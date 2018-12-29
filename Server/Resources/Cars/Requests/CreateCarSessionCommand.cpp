#include "CreateCarSessionCommand.h"

void from_json(const nlohmann::json& json, CreateCarSessionCommand& command) {
    command.position = json.at("position").get<int>();
    command.speed = json.at("speed").get<double>();
    command.socket = 0;
}