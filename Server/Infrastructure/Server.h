#pragma once
#include "functional"
#include <string>

#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"
#include "ListenOptions.h"

class Server {
    private:
        std::function<void(std::string)> concurrentHandler = [](std::string requestJson) {};
        GenericResult<int>* CreateSocket(); 
        Result* Bind(GenericResult<int>* socket, int port);
        Result* Listen(GenericResult<int>* socketResult);

    public:
        Server* HandleConcurrentClientsUsing(std::function<void(std::string)> handler);
        GenericResult<ListenOptions*>* Listen(int port);
        std::function<void(std::string)> GetConcurrentHandler();
};