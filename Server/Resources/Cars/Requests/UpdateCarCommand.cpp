#include "UpdateCarCommand.h"

void from_json(const nlohmann::json& json, UpdateCarCommand& command) {
    command.carId = json.at("carId").get<std::string>();
    command.speed = json.at("speed").get<double>();
    command.position = json.at("position").get<int>();
}