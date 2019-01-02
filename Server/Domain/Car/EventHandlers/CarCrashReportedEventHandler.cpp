#include "CarCrashReportedEventHandler.h"
#include "Server/Infrastructure/Server.h"
#include "Server/Infrastructure/Persistence/CarRepository.h"
#include "Server/Domain/WorldMap/WorldMap.h"

void CarCrashReportedEventHandler::Handle(CarCrashReportedEvent* event) {
    auto crash = event->GetCrash();
    auto cars = CarRepository::Find([crash](Car* car) {
        return car->IsCloseTo(crash);
    });

    auto streetOrNothing = WorldMap::StreetAt(crash->GetPosition());
    streetOrNothing->OnSuccess([&](WorldStreet* street) {
        for(auto car: cars) {
            auto notification = this->GetNotificationMessage(car, crash, street);            

            Server::WriteToClient(car->GetSocket(), Response::Notification(std::string(notification)));
        }
    });
}

std::string CarCrashReportedEventHandler::GetNotificationMessage(Car* car, WorldCarCrash* crash, WorldStreet* street) {
    auto distance = abs(crash->GetPosition() - car->GetPosition());

    if(car->GetPosition() <= crash->GetPosition()) {
        char notification[255];
        sprintf(notification, "[WARNING] Crash up ahead on street %s! %d miles left", street->GetName().c_str(), distance);

        return std::string(notification);
    }

    char notification[255];
    sprintf(notification, "[INFO] A car crash has been reported on street %s, only %d miles behind you!", street->GetName().c_str(), distance);

    return std::string(notification);
}