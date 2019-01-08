#include "../Infrastructure/Client.h"
#include "../Infrastructure/ConnectedClient.h"

#include "TrafficGuideClient.h"

void TrafficGuideClient::Run() {
    auto client = new Client();
    client
        ->Connect("127.0.0.1", 8080)
        ->OnSuccess([](auto socket) {
            auto connectedClient = new ConnectedClient(socket);
        })
        ->OnFail([]() {
            printf("[client] Could not connect to server\n");
        });
}