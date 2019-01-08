#pragma once

#include "string"
#include "Server/Resources/Common/ResourceRequest.h"
#include "Kernel/3rdParties/json.hpp"

class ReportCrashCommand : public ResourceRequest {
    public:
        std::string carId;
};

void from_json(const nlohmann::json& json, ReportCrashCommand& command);