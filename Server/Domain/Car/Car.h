#pragma once
#include "Kernel/Identity/Guid.h"
#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"

#include "../News/NewsSubscription.h"
#include "../News/NewsMessage.h"
#include "../WorldMap/WorldCarCrash.h"

class Car {
    private:
        Car(int socket, int position, double speed);
        Guid id;
        int socket;
        int position;
        double speed;

        std::vector<NewsSubscription*> subscriptions;
    public:
        static GenericResult<Car*>* Create(int socket, int position, double speed);
        Guid GetId();
        int GetSocket();
        int GetPosition();
        double GetSpeed();
        Result* Update(int position, double speed);
        Result* SubscribeTo(NewsType type);
        bool IsInterestedIn(NewsMessage* message);
        bool IsCloseTo(WorldCarCrash* crash);
};