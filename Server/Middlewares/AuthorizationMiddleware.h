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
        AuthorizationMiddleware(int clientSocket, Server* server): Middleware(clientSocket, server) {
            this->client = clientSocket;
        }
        bool Invoke(Request request) {
            if(!this->RequestNeedsAuthorization(request)) {
                return true;
            }

            auto tokenHeader = request.headers.find(TOKEN_KEY);
            if(tokenHeader == request.headers.end()) {
                return false;
            }

            auto token = request.headers[TOKEN_KEY];
            auto clients = CarRepository::GetAll();
            for(auto client: clients) {
                if(client->GetId().ToString() == token) {
                    return true;
                }
            }

            WriteToClient(Response::Unauthorized());
            return false;
        } 
};