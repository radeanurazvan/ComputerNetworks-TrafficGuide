#include "CarEvents.h"
#include "UnreachableCarDetectedEvent.h"

#include "Server/Events/DomainEvents.h"
#include "Server/Infrastructure/Persistence/CarRepository.h"

void CarEvents::Setup() {
    DomainEvents::Subscribe<UnreachableCarDetectedEvent>([](DomainEvent* event) {
        auto castedEvent = (UnreachableCarDetectedEvent*) event;
        CarRepository::DeleteWhere([castedEvent](Car* car) {
            return car->GetSocket() == castedEvent->client;
        });
    });
}