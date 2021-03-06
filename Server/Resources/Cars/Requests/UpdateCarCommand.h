#pragma once
#include <string>
#include "Kernel/3rdParties/json.hpp"

#include "Server/Resources/Common/ResourceRequest.h"

class UpdateCarCommand : public ResourceRequest{
    public:
        std::string carId;
        int position;
        double speed;
};

void from_json(const nlohmann::json& json, UpdateCarCommand& command);