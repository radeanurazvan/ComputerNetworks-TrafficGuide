#pragma once

#include "Kernel/Communication/Response.h"
#include "Server/Resources/Common/ServerResource.h"
#include "Requests/NewsSubscribeCommand.h"

class NewsController : public ServerResource{
    private:
        Response Subscribe(NewsSubscribeCommand* command);
    public:
        std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap();
};