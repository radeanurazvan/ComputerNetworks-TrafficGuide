#include "NewsSubscribeCommandContract.h"

void to_json(nlohmann::json& j, const NewsSubscribeCommandContract& command) {
    j = nlohmann::json {
        { "carId", command.carId },
        { "type", command.type }
    };
}