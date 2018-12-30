#include "CarsController.h"

#include "Server/Infrastructure/Persistence/CarRepository.h"
#include "Server/Resources/Common/ConcreteControllerResourceAdapter.h"
#include "Requests/CreateCarSessionCommand.h"

#include "Server/Domain/Car/Car.h"

CarsController::CarsController(int clientSocket) {
    this->clientSocket = clientSocket;
}

Response CarsController::CreateCarSession(CreateCarSessionCommand* command) {
    auto carOrFail = Car::Create(command->socket, command->position, command->speed);
    auto carIdResult = carOrFail
        ->OnSuccess([](Car* car) {
            CarRepository::Add(car);
        })
        ->Map<std::string>([](Car* car) {
        return GenericResult<std::string>::Ok(car->GetId().ToString());
        });

    return this->ResponseFromResult(carIdResult);
}

Response CarsController::UpdateCar(UpdateCarCommand* command) {
    auto carOrNothing = CarRepository::GetById(Guid(command->carId));

    auto updateResult = carOrNothing->Map([command](Car* car) {
        return car->Update(command->position, command->speed);
    });

    return this->ResponseFromResult(updateResult);
}

std::map<std::string, ControllerResourceAdapter*> CarsController::GetAdaptersMap() {
    std::map<std::string, ControllerResourceAdapter*> adaptersMap;

    auto createCarSessionAdapter = new ConcreteControllerResourceAdapter<CreateCarSessionCommand>([&](ResourceRequest* request) {
        auto command = (CreateCarSessionCommand*)request;
        command->socket = this->clientSocket;

        return this->CreateCarSession(command);
    });
    auto updateCarAdapter = new ConcreteControllerResourceAdapter<UpdateCarCommand>([&](ResourceRequest* request) {
        auto command = (UpdateCarCommand*)request;

        return this->UpdateCar(command);
    });

    adaptersMap["createSession"] = createCarSessionAdapter->NotGuardedByAuthorization();
    adaptersMap["update"] = updateCarAdapter;

    return adaptersMap;
}