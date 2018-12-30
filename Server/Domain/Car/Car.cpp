#include "Car.h"

Car::Car(int socket, int position, double speed) {
    this->id = Guid::NewGuid();

    this->socket = socket;
    this->position = position;
    this->speed = speed;
}

GenericResult<Car*>* Car::Create(int socket, int position, double speed) {
    if(position<0 || speed<0) {
        return GenericResult<Car*>::Fail("Bad car info");
    }

    return GenericResult<Car*>::Ok(new Car(socket, position, speed));
}

Result* Car::Update(int position, double speed) {
    if(position<0 || speed<0) {
        return Result::Fail("Bad car info");
    }

    this->position = position;
    this->speed = speed;

    return Result::Ok();
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