#include "NewsSubscribeCommand.h"

void from_json(const nlohmann::json& json, NewsSubscribeCommand& command) {
    command.carId = json.at("carId").get<std::string>();
    command.type = json.at("type").get<NewsType>();
}