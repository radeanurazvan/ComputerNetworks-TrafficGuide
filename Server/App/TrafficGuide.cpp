#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/ListeningServer.h"
#include "Server/Infrastructure/ListenOptions.h"

#include "TrafficGuide.h"

TrafficGuide::TrafficGuide() {}

void TrafficGuide::Run()
{
    auto server = new Server();
    server
        ->HandleConcurrentClientsUsing([](std::string requestJson) {
            printf("[server]Handling starting for request %s\n", requestJson.c_str());
        })
        ->Listen(8080)
        ->OnSuccess([server](ListenOptions* options) {
            auto listeningServer = new ListeningServer(server, options->GetSocket(), options->GetPort());
            listeningServer->ConcurrentServe();
        });
}