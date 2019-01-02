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

    Server::WriteToClient(clientSocket, Response::Ok<std::string>(connectionId.ToString()));

    return connectionId;
}

ListeningServer* ListeningServer::WithConnectionIdentityGeneratedBy(std::function<Guid(int)> generator)
{
    this->connectionIdentityGenerator = generator;
    return this;
}

void ListeningServer::ConcurrentServe()
{
    sockaddr_in from;
    int length = sizeof(from);

    while (1)
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

        auto clientHandlingThread = std::thread([&]() {
            auto socketIsHealthy = true;
            while(socketIsHealthy) {
                auto requestOrFail = server->ReadFromClient(client);
                requestOrFail
                    ->OnSuccess([&](Request request){
                        auto finalizer = [&]() {
                            return this->concurrentHandler(client, connectionId, request);
                        };

                        RequestPipeline pipeline = { 
                            new ModelValidationMiddleware(),
                            new AuthorizationMiddleware()
                        };
                        pipeline = pipeline
                            .ForClient(client)
                            .ForServer(this->server)
                            .WithFinalizer(finalizer);
                        pipeline.Run(request);
                    })
                    ->OnFail([&socketIsHealthy]() {
                        socketIsHealthy = false;
                    });
            }

            printf("[server] Client closed connection\n");
            Server::CloseSocket(client);
        });

        clientHandlingThread.detach();
        
    }
    printf("[server] While server terminated\n");
}