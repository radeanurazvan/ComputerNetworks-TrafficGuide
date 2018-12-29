#pragma once
#define TOKEN_KEY "token"

#include "Server/Infrastructure/Persistence/CarRepository.h"
#include "Server/Scaffolding/ServerScaffolder.h"
#include "Middleware.h"


class AuthorizationMiddleware : public Middleware {
    private:
        int client;
        bool RequestNeedsAuthorization(Request request) {
            auto scaffolder = new ServerScaffolder(this->client);
            auto scaffoldingRequest = ScaffoldingRequest(request.resource);
            auto adapterOrFail = scaffolder->MethodAdapterForRequest(scaffoldingRequest);

            if(!adapterOrFail->IsValid()) {
                return true;
            }             

            auto adapter = adapterOrFail->GetValue();
            return adapter->NeedsAuthorization();
        }
    public:
        AuthorizationMiddleware(int client) : Middleware() {
            this->client = client;
        }
        Response Invoke(Request request, std::function<Response()> next) {
            if(!this->RequestNeedsAuthorization(request)) {
                return next();
            }

            auto tokenHeader = request.headers.find(TOKEN_KEY);
            if(tokenHeader == request.headers.end()) {
                return Response::Unauthorized();
            }

            auto token = request.headers[TOKEN_KEY];
            auto clients = CarRepository::GetAll();
            for(auto client: clients) {
                if(client->GetId().ToString() == token) {
                    return next();
                }
            }

            return Response::Unauthorized();
        } 
};