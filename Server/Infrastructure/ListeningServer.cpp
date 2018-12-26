#include <netinet/in.h>
#include <thread>

#include "ListeningServer.h"

ListeningServer::ListeningServer(Server* server, int socketDescriptor, int port)
{
    this->server = server;
    this->socket = socketDescriptor;
    this->port = port;
}

void ListeningServer::ConcurrentServe()
{
    sockaddr_in from;

    while (1)
    {
        int client;
        int length = sizeof(from);

        printf("Server waiting on port %d...\n", this->port);
        fflush(stdout);

        if ((client = accept(this->socket, (struct sockaddr *)&from, &length)) < 0)
        {
            perror("Server accept error.\n");
            continue;
        }
        
        auto clientThread = std::thread(this->server->GetConcurrentHandler());
        clientThread.detach();
    }
}