#include "MiddlewareInPipeline.h"

MiddlewareInPipeline::MiddlewareInPipeline(Middleware* middleware, std::function<Response()> next) {
    this->middleware = middleware;
    this->next = next;
}

Response MiddlewareInPipeline::Invoke(Request request) {
    return this->middleware->Invoke(request, this->next);
}
