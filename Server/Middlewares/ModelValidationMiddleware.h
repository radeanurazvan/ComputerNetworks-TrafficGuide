#pragma once
#include "Middleware.h"

class ModelValidationMiddleware : public Middleware {
    public:
        ModelValidationMiddleware(int clientSocket, Server* server) : Middleware(clientSocket, server) {} 
        bool Invoke(Request request) {
            if(!request.IsValid()){
                this->WriteToClient(Response::BadRequest("Cannot deserialize request"));
                return false;
            }

            return true;
        }
};