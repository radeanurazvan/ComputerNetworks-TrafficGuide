#pragma once

#include "Kernel/Functional/GenericResult.h"
#include "Kernel/Functional/Result.h"

class Client {
    private:
        GenericResult<int>* GetSocket();
    public:
        Result* Connect(const char* address, int port);
};