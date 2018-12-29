#include "Middleware.h"

Middleware::Middleware(int clientSocket, Server* server) {
    this->clientSocket = clientSocket;
    this->server = server;
}

void Middleware::WriteToClient(Response response) {
    this->server->WriteToClient(this->clientSocket, response);
}
