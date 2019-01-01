#pragma once 
#include "Server/Events/DomainEvent.h"

class CarConnectedEvent : public DomainEvent {
    private:
        int socket;
    public:
        CarConnectedEvent(int socket) {
            this->socket = socket;
        }
        int GetSocket() {
            return this->socket;
        }
};