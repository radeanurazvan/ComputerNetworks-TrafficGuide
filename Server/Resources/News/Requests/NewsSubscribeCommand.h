#pragma once

#include <string>
#include "Server/Domain/News/NewsType.h"
#include "Server/Resources/Common/ResourceRequest.h"
#include "Kernel/3rdParties/json.hpp"

class NewsSubscribeCommand : public ResourceRequest {
    public:
        std::string carId;
        NewsType type;
};

void from_json(const nlohmann::json& json, NewsSubscribeCommand& command);