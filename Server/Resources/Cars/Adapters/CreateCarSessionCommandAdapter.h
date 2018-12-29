#pragma once
#include "Kernel/Helpers/JsonHelper.h"

#include "Server/Resources/Common/ControllerResourceAdapter.h"
#include "Server/Resources/Cars//Requests/CreateCarSessionCommand.h"

class CreateCarSessionCommandAdapter : public ControllerResourceAdapter {
    protected:
        GenericResult<ResourceRequest*>* AdaptRequest(std::string request) {
            if(!JsonHelper::CanParse<CreateCarSessionCommand>(request)) {
                return GenericResult<ResourceRequest*>::Fail("Bad request");
            }

            auto command = JsonHelper::Parse<CreateCarSessionCommand>(request);
            return GenericResult<ResourceRequest*>::Ok(&command);
        }
    public:
        CreateCarSessionCommandAdapter(std::function<Response(ResourceRequest*)> controllerMethod) : ControllerResourceAdapter(controllerMethod) {}
};