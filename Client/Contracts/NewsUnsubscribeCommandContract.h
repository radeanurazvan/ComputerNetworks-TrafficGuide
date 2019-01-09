#pragma once
#include "string"
#include "Kernel/3rdParties/json.hpp"

class NewsUnsubscribeCommandContract {
    public:
        std::string carId;
        int type;
};

void to_json(nlohmann::json& j, const NewsUnsubscribeCommandContract& command);