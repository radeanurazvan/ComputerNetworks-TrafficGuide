#pragma once

#include <map>
#include <string>
#include <functional>

#include "Kernel/Communication/Response.h"
#include "ControllerResourceAdapter.h"

class ServerResource {
    public:
        virtual std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap() = 0;
};