#pragma once

#include "Kernel/Functional/GenericResult.h"
#include "Kernel/Functional/Result.h"
#include "Kernel/Communication/Response.h"


class Client {
    private:
        GenericResult<int>* GetSocket();

    public:
        GenericResult<int>* Connect(const char* address, int port);
};