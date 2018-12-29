#pragma once
#include "Kernel/3rdParties/json/single_include/nlohmann/json.hpp"
#include "Server/Resources/Common/ResourceRequest.h"

class CreateCarSessionCommand : public ResourceRequest{
    public:
        int position;
        double speed;
};

void from_json(const nlohmann::json& json, CreateCarSessionCommand& command);