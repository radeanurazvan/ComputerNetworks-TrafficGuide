#include "ReportCrashCommand.h"

void from_json(const nlohmann::json& json, ReportCrashCommand& command) {
    command.carId = json.at("carId").get<std::string>();
}