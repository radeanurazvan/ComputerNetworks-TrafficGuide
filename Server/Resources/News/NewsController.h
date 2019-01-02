#pragma once

#include "Kernel/Communication/Response.h"
#include "Server/Resources/Common/ServerResource.h"

#include "Requests/NewsSubscribeCommand.h"
#include "Requests/NewsUnsubscribeCommand.h"

class NewsController : public ServerResource{
    private:
        Response Subscribe(NewsSubscribeCommand* command);
        Response Unsubscribe(NewsUnsubscribeCommand* command);
    public:
        std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap();
};