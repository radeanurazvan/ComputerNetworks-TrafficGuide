#pragma once

#include <vector>

#include "Kernel/Communication/Request.h"
#include "Server/Middlewares/Middleware.h"

class RequestPipeline {
    private:
        std::vector<Middleware*> middlewares;
        std::function<Response()> finalizer;
        Server* server;
        int client;
    public:
        RequestPipeline(std::initializer_list<Middleware*> middlewares);
        RequestPipeline ForServer(Server* server);
        RequestPipeline ForClient(int client);
        RequestPipeline WithFinalizer(std::function<Response()> finalizer);
        void Run(Request request);
};