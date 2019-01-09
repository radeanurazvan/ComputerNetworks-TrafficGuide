#pragma once
#include "string"
#include "Kernel/3rdParties/json.hpp"

class ReportCrashCommandContract {
    public:
        std::string carId;
};

void to_json(nlohmann::json& j, const ReportCrashCommandContract& command);