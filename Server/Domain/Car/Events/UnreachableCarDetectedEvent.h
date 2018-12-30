#pragma once

#include "Server/Events/DomainEvent.h"

class UnreachableCarDetectedEvent : public DomainEvent {
    private:
        int client;
    public:
        UnreachableCarDetectedEvent(int client) {
            this->client = client;
        }
        int GetClient() {
            return this->client;
        }
};