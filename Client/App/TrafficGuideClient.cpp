#include "Kernel/Jobs/RecurrentJobs.h"
#include "Kernel/Jobs/Seconds.h"
#include "../Infrastructure/Client.h"
#include "../Infrastructure/ConnectedClient.h"
#include "../Domain/Car.h"
#include "../Contracts/UpdateCarCommandContract.h"
#include "../Contracts/NewsSubscribeCommandContract.h"
#include "../Contracts/NewsUnsubscribeCommandContract.h"
#include "../Contracts/ReportCrashCommandContract.h"

#include "TrafficGuideClient.h"

Car* TrafficGuideClient::currentCar;

void TrafficGuideClient::Run() {
    auto client = new Client();
    client
        ->Connect("127.0.0.1", 8080)
        ->OnSuccess([](auto socket) {
            auto connectedClient = new ConnectedClient(socket);
            printf("[client] Created connected client\n");
            connectedClient->OnTokenAcquired([connectedClient](std::string token) {
                auto car = Car::Random(token);
                TrafficGuideClient::currentCar = car;
                printf("[client] Car connected. Id: %s, Position: %d, Speed: %g\n\n", car->GetId().c_str(), car->GetPosition(), car->GetSpeed());
                TrafficGuideClient::SetupJobs(car, connectedClient);
            });
            connectedClient->WithCommandContract<NewsSubscribeCommandContract>("news/subscribe", [](ClientInput* input) {
                auto params = input->GetParameters();
                auto newsType = atoi(params["type"].c_str());
                return NewsSubscribeCommandContract { TrafficGuideClient::currentCar->GetId(), newsType };
            });
            connectedClient->WithCommandContract<NewsUnsubscribeCommandContract>("news/unsubscribe", [](ClientInput* input) {
                auto params = input->GetParameters();
                auto newsType = atoi(params["type"].c_str());
                return NewsUnsubscribeCommandContract { TrafficGuideClient::currentCar->GetId(), newsType };
            });
            connectedClient->WithCommandContract<ReportCrashCommandContract>("cars/reportCrash", [](ClientInput* input) {
                return ReportCrashCommandContract { TrafficGuideClient::currentCar->GetId() };
            });
            connectedClient->Run();
        })
        ->OnFail([]() {
            printf("[client] Could not connect to server\n");
        });
}

void TrafficGuideClient::SetupJobs(Car* car, ConnectedClient* connectedClient) {
    RecurrentJobs::Schedule([car, connectedClient]() {
        car->Update();
        auto command = UpdateCarCommandContract { car->GetId() , car->GetPosition(), car->GetSpeed()};
        connectedClient->WriteRequest<UpdateCarCommandContract>("cars/update", command);
    }, Seconds::FromMinutes(1));
}