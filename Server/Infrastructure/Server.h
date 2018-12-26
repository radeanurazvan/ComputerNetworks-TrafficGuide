#pragma once
#include "functional"

#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"
#include "ListenOptions.h"

class Server {
    private:
        std::function<void()> concurrentHandler = []() {};
        GenericResult<int>* CreateSocket(); 
        Result* Bind(GenericResult<int>* socket, int port);
        Result* Listen(GenericResult<int>* socketResult);

    public:
        Server* HandleConcurrentClientsUsing(std::function<void()> handler);
        GenericResult<ListenOptions*>* Listen(int port);
        std::function<void()> GetConcurrentHandler();
};