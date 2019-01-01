#pragma once
#include <map>
#include "Server/Resources/Common/ServerResource.h"

#include "Requests/UpdateCarCommand.h"
#include "Requests/ReportCrashCommand.h"

class CarsController : public ServerResource {
    private:
        Response UpdateCar(UpdateCarCommand* command);
        Response ReportCrash(ReportCrashCommand* command);
    public:
        std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap();
};