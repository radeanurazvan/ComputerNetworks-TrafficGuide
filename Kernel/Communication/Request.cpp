#include "Request.h"
#include "../Helpers/JsonHelper.h"

Request::Request() {
}

Request Request::FromJson(std::string json) {
    auto request = Request();
    if(!JsonHelper::IsValidJson(json)) {
        request.isValid = false;
        return request;
    }

    if(!JsonHelper::CanParse<Request>(json)) {
        request.isValid = false;
        return request;    
    }

    return JsonHelper::Parse<Request>(json);
}

bool Request::IsValid() {
    return this->isValid;
}

void from_json(const nlohmann::json& json, Request& request) {
    request.headers = json.at("headers").get<std::map<std::string, std::string>>();
    request.body = json.at("body").get<std::string>();
    request.resource = json.at("resource").get<std::string>();
}