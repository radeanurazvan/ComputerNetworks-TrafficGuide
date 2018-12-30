#pragma once

#include "../Requests/NewsSubscribeCommand.h"
#include "Server/Resources/Common/ConcreteControllerResourceAdapter.h"

class NewsSubscribeCommandAdapter : public ConcreteControllerResourceAdapter<NewsSubscribeCommand> {
    protected:
        bool ValidateRequest(NewsSubscribeCommand* request) {
            auto typeAsInt = (int)request->type;
            if(typeAsInt > 3 || typeAsInt < 1) {
                return false;
            }

            return true;
        };
    public:
        NewsSubscribeCommandAdapter(std::function<Response(ResourceRequest*)> controllerMethod): 
            ConcreteControllerResourceAdapter( controllerMethod) {
            }
};