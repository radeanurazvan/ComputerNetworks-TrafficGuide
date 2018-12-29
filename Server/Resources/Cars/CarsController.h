#pragma once
#include <map>
#include "Server/Resources/Common/ServerResource.h"

#include "Requests/CreateCarSessionCommand.h"
#include "Adapters/CreateCarSessionCommandAdapter.h"

class CarsController : public ServerResource {
    private:
        int clientSocket;
        Response CreateCarSession(CreateCarSessionCommand* command);
    public:
        CarsController(int clientSocket);
        std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap();
};