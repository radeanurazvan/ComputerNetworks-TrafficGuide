#pragma once
#include "Middleware.h"

class ModelValidationMiddleware : public Middleware {
    public:
        Response Invoke(Request request, std::function<Response()> next) {
            if(!request.IsValid()){
                return Response::BadRequest("Cannot deserialize request");
            }

            return next();
        }
};