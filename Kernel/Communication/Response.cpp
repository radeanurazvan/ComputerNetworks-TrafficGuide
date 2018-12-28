#include "Response.h"

Response::Response() {
}


Response::Response(int code, std::string body) {
    this->code = code;
    this->body = body;
}

Response Response::BadRequest(std::string reason = "") {
    return Response(HttpCode::BadRequest, std::string(reason));
}

Response Response::Unauthorized() {
    return Response(HttpCode::Unauhtorized, std::string(""));
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
