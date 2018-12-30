#pragma once

#include "Server/Domain/WorldMap/WorldCarCrash.h"
#include "Server/Events/DomainEvent.h"

class CarCrashReportedEvent : public DomainEvent {
    private:
        WorldCarCrash* crash;
    public:
        CarCrashReportedEvent(WorldCarCrash* crash) {
            this->crash = crash;
        }
        WorldCarCrash* GetCrash() {
            return this->crash;
        }
};