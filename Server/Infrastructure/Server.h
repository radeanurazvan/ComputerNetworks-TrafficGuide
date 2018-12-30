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
        std::function<Response(int, Request)> concurrentHandler = [](int clientSocket, Request request) { return Response::Ok<std::string>(""); };
        GenericResult<int>* CreateSocket(); 
        Result* Bind(GenericResult<int>* socket, int port);
        Result* Listen(GenericResult<int>* socketResult);

    public:
        Server* HandleConcurrentClientsUsing(std::function<Response(int, Request)> handler);
        GenericResult<ListenOptions*>* Listen(int port);
        std::function<Response(int, Request)> GetConcurrentHandler();
        GenericResult<Request>* ReadFromClient(int clientSocket);
        static Result* WriteToClient(int clientSocket, Response message);
        static void CloseSocket(int socket);
};