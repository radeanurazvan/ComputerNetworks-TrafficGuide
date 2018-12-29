#pragma once

#include "Kernel/Communication/Request.h"
#include "Kernel/Communication/Response.h"

#include "Server/Infrastructure/Server.h"

class Middleware {
    public:
        virtual Response Invoke(Request request, std::function<Response()> next) = 0;
};