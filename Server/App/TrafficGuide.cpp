#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/ListeningServer.h"
#include "Server/Infrastructure/ListenOptions.h"

#include "Server/Resources/Authentication/AuthenticationController.h"
#include "Server/Scaffolding/ScaffoldingRequest.h"
#include "Server/Scaffolding/ServerScaffolder.h"

#include "TrafficGuide.h"

TrafficGuide::TrafficGuide() {}

void TrafficGuide::Run()
{
    auto server = new Server();
    server
        ->HandleConcurrentClientsUsing([server](int clientSocket, Request clientRequest) {
            auto serverScaffolder = new ServerScaffolder();

            printf("[server] Handling starting\n");

            auto scaffoldingRequest = new ScaffoldingRequest(clientRequest.resource);

            printf("[server] Identified controller %s and method %s \n", scaffoldingRequest->GetController().c_str(), scaffoldingRequest->GetMethod().c_str());

            auto methodOrFail = serverScaffolder->MethodForRequest(*scaffoldingRequest);
            
            methodOrFail
                ->OnSuccess([clientSocket, server](std::function<Response(ResourceRequest*)> method) {
                    auto response = method(new ResourceRequest());
                    server->WriteToClient(clientSocket, response);
                })
                ->OnFail([clientSocket, server, methodOrFail]() {
                    server->WriteToClient(clientSocket, Response::BadRequest(methodOrFail->GetErrorMessage()));
                });
        })
        ->Listen(8080)
        ->OnSuccess([server](ListenOptions* options) {
            auto listeningServer = new ListeningServer(server, options->GetSocket(), options->GetPort());
            listeningServer->ConcurrentServe();
        });
}