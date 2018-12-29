#pragma once
#include "string.h"

#include "Kernel/Communication/Response.h"
#include "Kernel/Functional/GenericResult.h"
#include "ResourceRequest.h"

class ControllerResourceAdapter {
    private:
        std::function<Response(ResourceRequest*)> controllerMethod;
    protected:
        ControllerResourceAdapter(std::function<Response(ResourceRequest*)> controllerMethod);
        virtual GenericResult<ResourceRequest*>* AdaptRequest(std::string request) = 0;
    public:
        GenericResult<Response>* GetResponse(std::string request);
};