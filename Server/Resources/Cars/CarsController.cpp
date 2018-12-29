#include "CarsController.h"

#include "Adapters/CreateCarSessionCommandAdapter.h"

#include "Requests/CreateCarSessionCommand.h"

#include "Server/Domain/Car/Car.h"

CarsController::CarsController(int clientSocket) {
    this->clientSocket = clientSocket;
}

Response CarsController::CreateCarSession(CreateCarSessionCommand* command) {
    auto carOrFail = Car::Create(command->socket, command->position, command->speed);
    auto carIdResult = carOrFail->Map<std::string>([](Car* car) {
        return GenericResult<std::string>::Ok(car->GetId().ToString());
    });

    return this->ResponseFromResult(carIdResult);
}

std::map<std::string, ControllerResourceAdapter*> CarsController::GetAdaptersMap() {
    std::map<std::string, ControllerResourceAdapter*> adaptersMap;

    auto createCarSessionAdapter = new CreateCarSessionCommandAdapter([&](ResourceRequest* request) {
        auto command = (CreateCarSessionCommand*)request;
        command->socket = this->clientSocket;

        return this->CreateCarSession(command);
    });
    adaptersMap["createSession"] = createCarSessionAdapter->NotGuardedByAuthorization();

    return adaptersMap;
}