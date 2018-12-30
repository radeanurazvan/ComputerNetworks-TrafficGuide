#pragma once

#include "ControllerResourceAdapter.h"

template <class T>
class ConcreteControllerResourceAdapter : public ControllerResourceAdapter {
    protected:
        virtual GenericResult<ResourceRequest*>* AdaptRequest(std::string request) {
            if(!JsonHelper::CanParse<T>(request)) {
                return GenericResult<ResourceRequest*>::Fail("Bad request");
            }
            auto command = JsonHelper::Parse<T>(request);
            auto commandCopy = new T(command);
            

            if(!ValidateRequest(commandCopy)) {
                return GenericResult<ResourceRequest*>::Fail("Bad request");                
            }
            
            return GenericResult<ResourceRequest*>::Ok(commandCopy);
        }
        virtual bool ValidateRequest(T* request){
            return true;
        }
    public:
        ConcreteControllerResourceAdapter(std::function<Response(ResourceRequest*)> controllerMethod) : 
            ControllerResourceAdapter(controllerMethod) {
            }
};