#pragma once

#include <map>
#include <string>
#include <functional>

#include "Kernel/Communication/Response.h"
#include "ResourceRequest.h"

class ServerResource {
    public:
        virtual std::map<std::string, std::function<Response(ResourceRequest*)>> GetResourceMap() = 0;
};