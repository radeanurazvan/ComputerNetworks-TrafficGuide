#pragma once

#include "Server/Events/DomainEvent.h"

class UnreachableCarDetectedEvent : public DomainEvent {
    public:
        int client;
        UnreachableCarDetectedEvent(int client) {
            this->client = client;
        }
};