#pragma once

#include "../Events/UnreachableCarDetectedEvent.h"

class UnreachableCarDetectedEventHandler {
    public:
        void Handle(UnreachableCarDetectedEvent* event);
};