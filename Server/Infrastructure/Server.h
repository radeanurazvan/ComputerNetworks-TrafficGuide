#pragma once


#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"

class Server {
    private:
        GenericResult<int>* CreateSocket(); 
        Result* Bind(GenericResult<int>* socket, int port);
        Result* Listen(GenericResult<int>* socketResult);

    public:
        Result* Listen(int port);
};