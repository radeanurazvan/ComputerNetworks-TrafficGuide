#pragma once

#include "string"
#include "Server/Domain/WorldMap/WorldStreet.h"
#include "../Events/CarCrashReportedEvent.h"
#include "../Car.h"

class CarCrashReportedEventHandler {
    private:
        std::string GetNotificationMessage(Car* car, WorldCarCrash* crash, WorldStreet* street);
    public:
        void Handle(CarCrashReportedEvent* event);
};