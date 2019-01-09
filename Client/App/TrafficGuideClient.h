#pragma once

#include "../Domain/Car.h"
#include "../Infrastructure/ConnectedClient.h"

class TrafficGuideClient {
    private:
        TrafficGuideClient();
        static Car* currentCar;
        static void SetupJobs(Car* car, ConnectedClient* connectedClient);
    public:
        static void Run();
};