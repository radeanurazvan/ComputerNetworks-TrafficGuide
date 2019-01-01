#include "Server/Domain/Car/Car.h"
#include "Server/Infrastructure/Persistence/CarRepository.h"
#include "CarConnectedEventHandler.h"

Guid CarConnectedEventHandler::Handle(CarConnectedEvent* event) {
    auto carResult = Car::Create(event->GetSocket(), 0, 0);
    auto car = carResult->GetValue();

    CarRepository::Add(car);
    return car->GetId();
}   