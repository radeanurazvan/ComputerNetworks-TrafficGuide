#include <sys/ioctl.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include "string.h"

#include "Kernel/Helpers/JsonHelper.h"

#include "ListeningServer.h"

#define MAX_REQUEST_SIZE 1024

ListeningServer::ListeningServer(Server* server, int socketDescriptor, int port)
{
    this->server = server;
    this->socket = socketDescriptor;
    this->port = port;
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
        auto request = this->ReadFromClient(client);
        if(!request.IsValid()){
            this->WriteToClient(client, Response::BadRequest());
            continue;
        }
        
        auto clientThread = std::thread(this->server->GetConcurrentHandler(), std::string(request.body));
        clientThread.detach();

        this->WriteToClient(client, Response::Ok<char*>("Succ\n"));
    }
}

Request ListeningServer::ReadFromClient(int clientSocket) {
    char* buffer = (char*)malloc(MAX_REQUEST_SIZE * sizeof(char));
    read(clientSocket, buffer, MAX_REQUEST_SIZE);
    
    printf("[server] Read from client: %s\n", buffer);
    return Request::FromJson(buffer);
}

void ListeningServer::WriteToClient(int clientSocket, Response message) {
    auto serializedMessage = JsonHelper::Serialize<Response>(message);
    write(clientSocket, serializedMessage.c_str(), serializedMessage.size());

    printf("[server] Wrote to client: %s\n", serializedMessage.c_str());
}