#pragma once
#include <string>
#include <map>
#include "Kernel/Functional/GenericResult.h"
#include "Server/Resources/Common/ServerResource.h"

#include "ScaffoldingRequest.h"

class ServerScaffolder {
    private:
        std::map<std::string, ServerResource*> GetServerResourcesMap();
        GenericResult<ServerResource*>* ControllerFor(std::string controller);
    public:
        GenericResult<ControllerResourceAdapter*>* MethodAdapterForRequest(ScaffoldingRequest request);
};