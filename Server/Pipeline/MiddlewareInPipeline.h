#pragma once
#include <functional>
#include "Kernel/Communication/Request.h"
#include "Kernel/Communication/Response.h"
#include "Server/Middlewares/Middleware.h"

class MiddlewareInPipeline {
    private:
        Middleware* middleware;
        std::function<Response()> next;
    public:
        MiddlewareInPipeline(Middleware* middleware, std::function<Response()> next);
        Response Invoke(Request request);
};