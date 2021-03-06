#include <sys/ioctl.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include "string.h"

#include "Kernel/Helpers/JsonHelper.h"
#include "Server/Middlewares/ModelValidationMiddleware.h"
#include "Server/Middlewares/AuthorizationMiddleware.h"

#include "Server/Pipeline/RequestPipeline.h"
#include "ListeningServer.h"

#define MAX_REQUEST_SIZE 1024

ListeningServer::ListeningServer(Server* server, int socketDescriptor, int port)
{
    this->server = server;
    this->socket = socketDescriptor;
    this->port = port;
}

ListeningServer* ListeningServer::HandleConcurrentClientsUsing(std::function<Response(int, Guid, Request)> handler)
{
    this->concurrentHandler = handler;
    return this;
}

Guid ListeningServer::AttachClientIdentity(int clientSocket) {
    auto connectionId = this->connectionIdentityGenerator(clientSocket);
    printf("\n\n[server] New client with connection id %s\n", connectionId.ToString().c_str());

    std::map<std::string, std::string> responseValues;
    responseValues["token"] = connectionId.ToString();
    
    Server::WriteToClient(clientSocket, Response::Ok<std::map<std::string, std::string>>(responseValues));

    return connectionId;
}

ListeningServer* ListeningServer::WithConnectionIdentityGeneratedBy(std::function<Guid(int)> generator)
{
    this->connectionIdentityGenerator = generator;
    return this;
}

ListeningServer* ListeningServer::OnConnectionClosed(std::function<void(Guid)> onConnectionClosed) {
    this->onConnectionClosed = onConnectionClosed;
    return this;
}

void ListeningServer::ConcurrentServe()
{
    sockaddr_in from;
    int length = sizeof(from);

    while (true)
    {
        int client;

        printf("[server] Server waiting on port %d...\n", this->port);
        fflush(stdout);

        if ((client = accept(this->socket, (struct sockaddr *)&from, &length)) < 0)
        {
            perror("[server] Server accept error.\n");
            continue;
        }
        auto connectionId = this->AttachClientIdentity(client);

        auto clientHandlingThread = std::thread([*this, client, connectionId]() {
            auto socketIsHealthy = true;
            while(socketIsHealthy) {
                auto requestOrFail = server->ReadFromClient(client);
                printf("\n\n---------Start of handling client %d----------\n", client);
                requestOrFail
                    ->OnSuccess([*this, client, connectionId](Request request){

                        auto finalizer = [*this, client, connectionId, request]() {
                            return this->concurrentHandler(client, connectionId, request);
                        };

                        RequestPipeline pipeline = { 
                            new ModelValidationMiddleware(),
                            new AuthorizationMiddleware()
                        };
                        pipeline = pipeline
                            .ForClient(client)
                            .ForServer(this->server)
                            .WithFinalizer(finalizer)
                            .OnConnectionClosed(this->onConnectionClosed);
                        pipeline.Run(request);
                    })
                    ->OnFail([&socketIsHealthy, client, connectionId]() {
                        socketIsHealthy = false;
                        printf("[server] Socket %d with id %s not healthy anymore\n\n", client, connectionId.ToString().c_str());
                    });

                printf("---------End of handling client %d----------\n\n", client);
            }

            printf("[server] Client closed connection\n");
            Server::CloseSocket(client);
            this->onConnectionClosed(connectionId);
        });

        clientHandlingThread.detach();
        
    }
    printf("[server] While server terminated\n");
}