#pragma once

#include <vector>

#include "Kernel/Identity/Guid.h"
#include "Kernel/Communication/Request.h"
#include "Server/Middlewares/Middleware.h"
#include "MiddlewareInPipeline.h"

class RequestPipeline {
    private:
        std::vector<Middleware*> middlewares;
        std::function<void(Guid)> onConnectionClosed;
        std::function<Response()> finalizer;
        Guid connectionId;
        Server* server;
        int client;
        std::vector<MiddlewareInPipeline*> GetChainedMiddlewares(Request request);
    public:
        RequestPipeline(std::initializer_list<Middleware*> middlewares);
        RequestPipeline ForServer(Server* server);
        RequestPipeline ForClient(int client);
        RequestPipeline WithConnectionId(Guid connectionId);
        RequestPipeline OnConnectionClosed(std::function<void(Guid)> onConnectionClosed);
        RequestPipeline WithFinalizer(std::function<Response()> finalizer);
        void Run(Request request);
};