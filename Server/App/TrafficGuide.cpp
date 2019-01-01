#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/ListeningServer.h"
#include "Server/Infrastructure/ListenOptions.h"

#include "Server/Scaffolding/ScaffoldingRequest.h"
#include "Server/Scaffolding/ServerScaffolder.h"

#include "Server/Events/DomainEvents.h"
#include "Server/Domain/Car/Events/CarConnectedEvent.h"
#include "Server/Domain/Car/EventHandlers/CarConnectedEventHandler.h"

#include "AppBootstrapper.h"
#include "TrafficGuide.h"

TrafficGuide::TrafficGuide() {}

void TrafficGuide::Run()
{
    auto server = new Server();
    server
        ->Listen(8080)
        ->OnSuccess([server](ListenOptions* options) {
            AppBootstrapper::Bootstrap();

            auto listeningServer = new ListeningServer(server, options->GetSocket(), options->GetPort());
            listeningServer
                ->WithConnectionIdentityGeneratedBy([](int clientSocket) {
                    auto handler = new CarConnectedEventHandler();
                    return handler->Handle(new CarConnectedEvent(clientSocket));
                })
                ->HandleConcurrentClientsUsing([server](int clientSocket, Guid connectionId, Request clientRequest) {
                    auto serverScaffolder = new ServerScaffolder();

                    printf("[server] Handling starting\n");

                    auto scaffoldingRequest = new ScaffoldingRequest(clientRequest.resource);

                    printf("[server] Identified controller %s and method %s \n", scaffoldingRequest->GetController().c_str(), scaffoldingRequest->GetMethod().c_str());

                    auto adapterOrFail = serverScaffolder->MethodAdapterForRequest(*scaffoldingRequest);
                    
                    Response handlingResponse;
                    adapterOrFail
                        ->OnSuccess([&](ControllerResourceAdapter* adapter) {
                            auto responseOrFail = adapter->GetResponse(clientRequest.body);
                            responseOrFail
                                ->OnSuccess([&](Response response) {
                                    handlingResponse = response;
                                })
                                ->OnFail([&]() {
                                    handlingResponse = Response::BadRequest(responseOrFail->GetErrorMessage());
                                });
                        })
                        ->OnFail([&]() {
                            handlingResponse = Response::BadRequest(adapterOrFail->GetErrorMessage());
                        });
                    
                    return handlingResponse;
            })
            ->ConcurrentServe();
        });
}