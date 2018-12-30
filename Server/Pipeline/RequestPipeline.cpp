#include "Server/Events/DomainEvents.h"

#include "RequestPipeline.h"
#include "MiddlewareInPipeline.h"

#include "Server/Domain/Car/Events/UnreachableCarDetectedEvent.h"

RequestPipeline::RequestPipeline(std::initializer_list<Middleware *> middlewares)
{
    this->middlewares = middlewares;
}

RequestPipeline RequestPipeline::ForServer(Server *server)
{
    this->server = server;
    return *this;
}

RequestPipeline RequestPipeline::ForClient(int client)
{
    this->client = client;
    return *this;
}

RequestPipeline RequestPipeline::WithFinalizer(std::function<Response()> finalizer) {
    this->finalizer = finalizer;
    return *this;
}

void RequestPipeline::Run(Request request)
{
    std::vector<MiddlewareInPipeline*> middlewaresInPipeline;

    printf("[server] Running pipeline...\n");
    auto lastMiddleware = middlewares.at(middlewares.size() - 1);
    auto lastMiddlewareInPipeline = new MiddlewareInPipeline(lastMiddleware, finalizer);
    middlewaresInPipeline.insert(middlewaresInPipeline.begin(), lastMiddlewareInPipeline);

    std::function<Response()> next = [lastMiddlewareInPipeline, request]() { return lastMiddlewareInPipeline->Invoke(request); };
    for (int i = middlewares.size() - 2; i >= 0; i--)
    {
        auto currentMiddleware = middlewares.at(i);
        auto currentMiddlewareInPipeline = new MiddlewareInPipeline(currentMiddleware, next);
        middlewaresInPipeline.insert(middlewaresInPipeline.begin(), currentMiddlewareInPipeline);
        
        next = [request, currentMiddlewareInPipeline]() {
            return currentMiddlewareInPipeline->Invoke(request);
        };
    }

    auto firstMiddleware = middlewaresInPipeline[0];
    auto response = firstMiddleware->Invoke(request);

    Server::WriteToClient(this->client, response)->OnFail([this]() {
        Server::CloseSocket(this->client);
        DomainEvents::Publish<UnreachableCarDetectedEvent>(new UnreachableCarDetectedEvent(this->client));
    });
}