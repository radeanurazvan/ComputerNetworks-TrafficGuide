#pragma once
#include "string"
#include "Kernel/3rdParties/json.hpp"

class NewsSubscribeCommandContract {
    public:
        std::string carId;
        int type;
};

void to_json(nlohmann::json& j, const NewsSubscribeCommandContract& command);