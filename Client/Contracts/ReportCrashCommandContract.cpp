#include "ReportCrashCommandContract.h"

void to_json(nlohmann::json& j, const ReportCrashCommandContract& command) {
    j = nlohmann::json {
        { "carId", command.carId },
    };
}