#pragma once
#include "Kernel/Identity/Guid.h"
#include "Kernel/Functional/GenericResult.h"

class Car {
    private:
        Car(int socket, int position, double speed);
        Guid id;
        int socket;
        int position;
        double speed;
    public:
        static GenericResult<Car*>* Create(int socket, int position, double speed);
        Guid GetId();
        int GetPosition();
        double GetSpeed();
};