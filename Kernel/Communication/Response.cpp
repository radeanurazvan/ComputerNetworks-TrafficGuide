#include "Response.h"

Response::Response() {
}


Response::Response(int code, std::string body) {
    this->code = code;
    this->body = body;
}

Response Response::BadRequest(std::string reason = "") {
    return Response(HttpCode::BadRequest, reason);
}

Response Response::Unauthorized() {
    return Response(HttpCode::Unauthorized, "");
}

Response Response::Custom(std::string body, int code) {
    return Response(code, body);
}


Response Response::Notification(std::string body) {
    return Response(HttpCode::Notification, body);
}

int Response::GetCode() const {
    return this->code;
}

std::string Response::GetBody() const {
    return this->body;
}

void to_json(nlohmann::json& j, const Response& response) {
    j = nlohmann::json{{"code", response.GetCode()}, {"body", response.GetBody()}};
}

void from_json(const nlohmann::json& json, Response& response) {
    auto code = json.at("code").get<int>();
    auto body = json.at("body").get<std::string>();

    response = Response::Custom(body, code);     
}