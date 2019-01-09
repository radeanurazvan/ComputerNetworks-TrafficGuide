#include "NewsUnsubscribeCommandContract.h"

void to_json(nlohmann::json& j, const NewsUnsubscribeCommandContract& command) {
    j = nlohmann::json {
        { "carId", command.carId },
        { "type", command.type }
    };
}