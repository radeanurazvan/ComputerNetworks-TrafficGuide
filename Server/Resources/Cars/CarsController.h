#pragma once
#include <map>
#include "Server/Resources/Common/ServerResource.h"

#include "Requests/CreateCarSessionCommand.h"
#include "Adapters/CreateCarSessionCommandAdapter.h"

class CarsController : public ServerResource {
    private:
        Response CreateCarSession(CreateCarSessionCommand* command);
    public:
        std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap();
};