#pragma once

#include "Kernel/Communication/Request.h"
#include "Server/Infrastructure/Server.h"

class Middleware {
    private:
        int clientSocket;
        Server* server;
    protected:
        Middleware(int clientSocket, Server* server);
        void WriteToClient(Response response);
    public:
        virtual bool Invoke(Request request) = 0;
};