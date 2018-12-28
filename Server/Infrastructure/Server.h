#pragma once
#include "functional"
#include <string>

#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"
#include "Kernel/Communication/Request.h"
#include "Kernel/Communication/Response.h"

#include "ListenOptions.h"

class Server {
    private:
        std::function<void(int, Request)> concurrentHandler = [](int clientSocket, Request request) {};
        GenericResult<int>* CreateSocket(); 
        Result* Bind(GenericResult<int>* socket, int port);
        Result* Listen(GenericResult<int>* socketResult);

    public:
        Server* HandleConcurrentClientsUsing(std::function<void(int, Request)> handler);
        GenericResult<ListenOptions*>* Listen(int port);
        std::function<void(int, Request)> GetConcurrentHandler();
        Request ReadFromClient(int clientSocket);
        void WriteToClient(int clientSocket, Response message);
};