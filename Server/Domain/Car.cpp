#include "Car.h"

Car::Car(int position, double speed) {
    this->id = Guid::NewGuid();

    this->position = position;
    this->speed = speed;
}

GenericResult<Car*>* Car::Create(int position, double speed) {
    if(position<0 || speed<0) {
        return GenericResult<Car*>::Fail("Bad car info");
    }

    return GenericResult<Car*>::Ok(new Car(position, speed));
}

Guid Car::GetId() {
    return this->id;
}

int Car::GetPosition() {
    return this->position;
}

double Car::GetSpeed() {
    return this->speed;
}