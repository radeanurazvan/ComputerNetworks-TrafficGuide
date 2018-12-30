#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/ListeningServer.h"
#include "Server/Infrastructure/ListenOptions.h"

#include "Server/Scaffolding/ScaffoldingRequest.h"
#include "Server/Scaffolding/ServerScaffolder.h"

#include "TrafficGuide.h"

TrafficGuide::TrafficGuide() {}

void TrafficGuide::Run()
{
    auto server = new Server();
    server
        ->HandleConcurrentClientsUsing([server](int clientSocket, Request clientRequest) {
            auto serverScaffolder = new ServerScaffolder(clientSocket);

            printf("[server] Handling starting\n");

            auto scaffoldingRequest = new ScaffoldingRequest(clientRequest.resource);

            printf("[server] Identified controller %s and method %s \n", scaffoldingRequest->GetController().c_str(), scaffoldingRequest->GetMethod().c_str());

            auto adapterOrFail = serverScaffolder->MethodAdapterForRequest(*scaffoldingRequest);
            
            adapterOrFail
                ->OnSuccess([clientSocket, clientRequest, server](ControllerResourceAdapter* adapter) {
                    auto responseOrFail = adapter->GetResponse(clientRequest.body);
                    responseOrFail
                        ->OnSuccess([&](Response response) {
                            Server::WriteToClient(clientSocket, response);
                        })
                        ->OnFail([clientSocket, server, responseOrFail]() {
                            Server::WriteToClient(clientSocket, Response::BadRequest(responseOrFail->GetErrorMessage()));
                        });
                })
                ->OnFail([clientSocket, server, adapterOrFail]() {
                    Server::WriteToClient(clientSocket, Response::BadRequest(adapterOrFail->GetErrorMessage()));
                });
        })
        ->Listen(8080)
        ->OnSuccess([server](ListenOptions* options) {
            auto listeningServer = new ListeningServer(server, options->GetSocket(), options->GetPort());
            listeningServer->ConcurrentServe();
        });
}