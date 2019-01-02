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

RequestPipeline RequestPipeline::WithConnectionId(Guid connectionId)
{
    this->connectionId = connectionId;
    return *this;
}

RequestPipeline RequestPipeline::OnConnectionClosed(std::function<void(Guid)> onConnectionClosed) {
    this->onConnectionClosed = onConnectionClosed;
    return *this;
}

RequestPipeline RequestPipeline::WithFinalizer(std::function<Response()> finalizer) {
    this->finalizer = finalizer;
    return *this;
}

void RequestPipeline::Run(Request request)
{

    printf("[server] Running pipeline...\n");
    auto chainedMiddlewares = this->GetChainedMiddlewares(request);    
    auto firstMiddleware = chainedMiddlewares[0];
    auto response = firstMiddleware->Invoke(request);

    Server::WriteToClient(this->client, response)->OnFail([this]() {
        printf("[server] Write failed for client %d, closing socket\n\n", this->client);
        
        Server::CloseSocket(this->client);
        this->onConnectionClosed(this->connectionId);
    });
}

std::vector<MiddlewareInPipeline*> RequestPipeline::GetChainedMiddlewares(Request request) {
    std::vector<MiddlewareInPipeline*> middlewaresInPipeline;    
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

    return middlewaresInPipeline;
}