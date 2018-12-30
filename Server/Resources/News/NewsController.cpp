#include "NewsController.h"

#include "Adapters/NewsSubscribeCommandAdapter.h"
#include "Server/Infrastructure/Persistence/CarRepository.h"

Response NewsController::Subscribe(NewsSubscribeCommand* command) {
    
    auto carOrNothing = CarRepository::GetById(Guid(command->carId));

    auto subscribeResult = carOrNothing->Map([command](Car* car) {
        return car->SubscribeTo(command->type);
    });

    return this->ResponseFromResult(subscribeResult);
}

std::map<std::string, ControllerResourceAdapter*> NewsController::GetAdaptersMap() {
    std::map<std::string, ControllerResourceAdapter*> adaptersMap;

    auto newsSubscribeAdapter = new NewsSubscribeCommandAdapter([this](ResourceRequest* request) {
        auto command = (NewsSubscribeCommand*) request;
        return this->Subscribe(command);
    });
    adaptersMap["subscribe"] = newsSubscribeAdapter;

    return adaptersMap;
}