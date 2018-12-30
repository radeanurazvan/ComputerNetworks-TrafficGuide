#pragma once
#include <map>
#include "Server/Resources/Common/ServerResource.h"

#include "Requests/CreateCarSessionCommand.h"
#include "Requests/UpdateCarCommand.h"
#include "Requests/ReportCrashCommand.h"

class CarsController : public ServerResource {
    private:
        int clientSocket;
        Response CreateCarSession(CreateCarSessionCommand* command);
        Response UpdateCar(UpdateCarCommand* command);
        Response ReportCrash(ReportCrashCommand* command);
    public:
        CarsController(int clientSocket);
        std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap();
};