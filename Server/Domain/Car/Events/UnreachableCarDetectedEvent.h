#pragma once

#include "Kernel/Identity/Guid.h"
#include "Server/Events/DomainEvent.h"

class UnreachableCarDetectedEvent : public DomainEvent {
    private:
        Guid connectionId;
    public:
        UnreachableCarDetectedEvent(Guid connectionId) {
            this->connectionId = connectionId;
        }
        Guid GetConnectionId() {
            return this->connectionId;
        }
};