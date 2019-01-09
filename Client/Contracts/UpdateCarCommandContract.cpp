#include "UpdateCarCommandContract.h"

void to_json(nlohmann::json& j, const UpdateCarCommandContract& command) {
    j = nlohmann::json {
        { "carId", command.carId },
        { "speed", command.speed },
        { "position", command.position }
    };
}