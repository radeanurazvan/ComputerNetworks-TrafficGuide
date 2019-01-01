#include "CarsController.h"

#include "Server/Infrastructure/Persistence/CarRepository.h"
#include "Server/Resources/Common/ConcreteControllerResourceAdapter.h"
#include "Server/Events/DomainEvents.h"
#include "Server/Domain/Car/Car.h"
#include "Server/Domain/Car/Events/CarCrashReportedEvent.h"
#include "Server/Domain/WorldMap/WorldMap.h"

Response CarsController::UpdateCar(UpdateCarCommand* command) {
    auto carOrNothing = CarRepository::GetById(Guid(command->carId));

    auto limitFeedbackResult = carOrNothing->Map<std::string>([command](Car* car) {
        auto updateResult = car->Update(command->position, command->speed); 
        if(!updateResult->IsValid()) {
            return GenericResult<std::string>::Fail(updateResult->GetErrorMessage());
        }

        return WorldMap::LimitFeedbackFor(car);
    });
    
    return this->ResponseFromResult(limitFeedbackResult, NotFound);
}

Response CarsController::ReportCrash(ReportCrashCommand* command) {
    auto carOrNothing = CarRepository::GetById(Guid(command->carId));
    auto result = carOrNothing->OnSuccess([](Car* car) {
        auto crash = WorldMap::CrashAt(car->GetPosition());
        DomainEvents::Publish<CarCrashReportedEvent>(new CarCrashReportedEvent(crash));
    })->ToSampleResult();

    return ResponseFromResult(result, NotFound);
}

std::map<std::string, ControllerResourceAdapter*> CarsController::GetAdaptersMap() {
    std::map<std::string, ControllerResourceAdapter*> adaptersMap;

    auto updateCarAdapter = new ConcreteControllerResourceAdapter<UpdateCarCommand>([&](ResourceRequest* request) {
        auto command = (UpdateCarCommand*)request;

        return this->UpdateCar(command);
    });
    auto reportCrashAdapter = new ConcreteControllerResourceAdapter<ReportCrashCommand>([&](ResourceRequest* request) {
        auto command = (ReportCrashCommand*)request;
        return this->ReportCrash(command);
    });

    adaptersMap["update"] = updateCarAdapter;
    adaptersMap["reportCrash"] = reportCrashAdapter;

    return adaptersMap;
}