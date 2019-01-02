#include "Server/Infrastructure/Persistence/CarRepository.h"
#include "UnreachableCarDetectedEventHandler.h"
#include "../Car.h"


void UnreachableCarDetectedEventHandler::Handle(UnreachableCarDetectedEvent* event) {
    CarRepository::DeleteWhere([event](Car* car) {
        return car->GetId() == event->GetConnectionId();
    });
    printf("[server] Deleted car with id %s\n\n", event->GetConnectionId().ToString().c_str());
}