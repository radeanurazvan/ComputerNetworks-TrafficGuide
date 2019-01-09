#include "Request.h"
#include "../Helpers/JsonHelper.h"

Request::Request() {
}

Request Request::InvalidRequest() {
    auto request = Request();
    request.isValid = false;

    return request;
}

Request Request::FromJson(std::string json) {
    if(!JsonHelper::IsValidJson(json)) {
        return InvalidRequest();
    }

    if(!JsonHelper::CanParse<Request>(json)) {
        return InvalidRequest();    
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

void to_json(nlohmann::json& j, const Request& request) {
    j = nlohmann::json {
        { "resource", request.resource },
        { "body", request.body },
        { "headers", request.headers }
    };
}