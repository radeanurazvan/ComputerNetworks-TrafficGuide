#pragma once

#include "string"
#include "../Events/CarConnectedEvent.h"
#include "Kernel/Identity/Guid.h"

class CarConnectedEventHandler {
    public:
        Guid Handle(CarConnectedEvent* event);
};