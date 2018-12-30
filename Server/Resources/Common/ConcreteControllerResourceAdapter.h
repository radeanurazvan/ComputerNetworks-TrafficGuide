#pragma once

#include "ControllerResourceAdapter.h"

template <class T>
class ConcreteControllerResourceAdapter : public ControllerResourceAdapter {
    protected:
        GenericResult<ResourceRequest*>* AdaptRequest(std::string request) {
            if(!JsonHelper::CanParse<T>(request)) {
                return GenericResult<ResourceRequest*>::Fail("Bad request");
            }

            auto command = JsonHelper::Parse<T>(request);
            auto commandCopy = new T(command);
            return GenericResult<ResourceRequest*>::Ok(commandCopy);
        }
    public:
        ConcreteControllerResourceAdapter(std::function<Response(ResourceRequest*)> controllerMethod) : 
            ControllerResourceAdapter(controllerMethod) {
            }
};