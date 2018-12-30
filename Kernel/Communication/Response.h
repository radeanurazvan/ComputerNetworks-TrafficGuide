#pragma once
#include "string.h"
#include "../Helpers/JsonHelper.h"
#include "../3rdParties/json/single_include/nlohmann/json.hpp"

enum HttpCode {
    Ok = 200,
    BadRequest = 400,
    Unauhtorized = 401,
    NotFound = 404,
    Notification = -1
};

class Response {
    private:
        Response(int code, std::string body);
        int code;
        std::string body;
    public:
        Response();
        template <class T>
        static Response Ok(T content);
        static Response BadRequest(std::string reason = "");
        static Response Unauthorized();
        static Response Custom(std::string body, int code);
        static Response Notification(std::string body);
        int GetCode() const ;
        std::string GetBody() const;
};

template <class T>
Response Response::Ok(T content) {
    return Response(HttpCode::Ok, JsonHelper::Serialize(content));
}

void to_json(nlohmann::json& json, const Response& response);

