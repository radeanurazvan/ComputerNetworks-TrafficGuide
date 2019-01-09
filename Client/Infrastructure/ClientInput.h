#pragma once

#include "string"
#include "map"
#include "Kernel/Functional/GenericResult.h"

class ClientInput {
    private:
        ClientInput(std::string resource, std::map<std::string, std::string>);
        std::string resource;
        std::map<std::string, std::string> parameters;
    public:
        static GenericResult<ClientInput*>* Create(std::string input);
        std::string GetResource();
        std::map<std::string, std::string> GetParameters();
};