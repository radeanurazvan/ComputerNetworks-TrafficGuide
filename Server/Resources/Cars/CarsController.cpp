#include "CarsController.h"

#include "Adapters/CreateCarSessionCommandAdapter.h"

#include "Requests/CreateCarSessionCommand.h"

#include "Server/Domain/Car.h"

CarsController::CarsController(int clientSocket) {
    this->clientSocket = clientSocket;
}

Response CarsController::CreateCarSession(CreateCarSessionCommand* command) {
    auto carOrFail = Car::Create(command->socket, command->position, command->speed);
    if(!carOrFail->IsValid()) {
        return Response::BadRequest(carOrFail->GetErrorMessage());
    }

    auto car = carOrFail->GetValue();
    return Response::Ok<std::string>(car->GetId().ToString());
}

std::map<std::string, ControllerResourceAdapter*> CarsController::GetAdaptersMap() {
    std::map<std::string, ControllerResourceAdapter*> adaptersMap;

    adaptersMap["createSession"] = new CreateCarSessionCommandAdapter([&](ResourceRequest* request) {
        auto command = (CreateCarSessionCommand*)request;
        command->socket = this->clientSocket;

        return this->CreateCarSession(command);
    });

    return adaptersMap;
}