#include <thread>

#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/ListeningServer.h"
#include "Server/Infrastructure/ListenOptions.h"

#include "TrafficGuide.h"

TrafficGuide::TrafficGuide() {}

void TrafficGuide::Run()
{
    auto server = new Server();
    server
        ->HandleConcurrentClientsUsing([]() {
            printf("Handling starting");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            printf("Sleep over");
        })
        ->Listen(8080)
        ->OnSuccess([server](ListenOptions* options) {
            auto listeningServer = new ListeningServer(server, options->GetSocket(), options->GetPort());
            listeningServer->ConcurrentServe();
        });

    printf("Everything went fine\n");
}