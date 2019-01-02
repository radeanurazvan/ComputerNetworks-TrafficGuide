#pragma once

#include "../Requests/NewsUnsubscribeCommand.h"
#include "Server/Resources/Common/ConcreteControllerResourceAdapter.h"

class NewsUnsubscribeCommandAdapter : public ConcreteControllerResourceAdapter<NewsUnsubscribeCommand> {
    protected:
        bool ValidateRequest(NewsUnsubscribeCommand* request) {
            auto typeAsInt = (int)request->type;
            if(typeAsInt > 3 || typeAsInt < 1) {
                return false;
            }

            return true;
        };
    public:
        NewsUnsubscribeCommandAdapter(std::function<Response(ResourceRequest*)> controllerMethod): 
            ConcreteControllerResourceAdapter( controllerMethod) {
            }
};