#pragma once

#include "string"
#include "Kernel/3rdParties/json.hpp"

class UpdateCarCommandContract {
    public:
        std::string carId;
        int position;
        double speed;
};

void to_json(nlohmann::json& j, const UpdateCarCommandContract& request);