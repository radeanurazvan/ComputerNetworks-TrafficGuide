#include <sys/ioctl.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include "string.h"

#include "Kernel/Helpers/JsonHelper.h"
#include "Server/Middlewares/ModelValidationMiddleware.h"
#include "Server/Middlewares/AuthorizationMiddleware.h"

#include "ListeningServer.h"

#define MAX_REQUEST_SIZE 1024

ListeningServer::ListeningServer(Server* server, int socketDescriptor, int port)
{
    this->server = server;
    this->socket = socketDescriptor;
    this->port = port;
}

std::vector<Middleware*> ListeningServer::GetMiddlewares(int client) {
    std::vector<Middleware*> middlewares;

    middlewares.push_back(new ModelValidationMiddleware(client, this->server));
    middlewares.push_back(new AuthorizationMiddleware(client, this->server));

    return middlewares;
}

bool ListeningServer::PassesMiddlewares(int client, Request request) {
    auto middlewares = this->GetMiddlewares(client);
    for(auto middleware: middlewares) {
        auto passedMiddleware = middleware->Invoke(request);
        if(!passedMiddleware) {
            return false;
        }
    }

    return true;
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
        printf("\n\n[server] New client\n");

        auto request = server->ReadFromClient(client);
        if(!this->PassesMiddlewares(client, request)) {
            continue;
        }

        auto clientThread = std::thread(this->server->GetConcurrentHandler(), client, request);
        clientThread.detach();
    }
}