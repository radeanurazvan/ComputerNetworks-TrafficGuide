#pragma once
#include <string>
#include "Kernel/3rdParties/json.hpp"

class Request {
    private:
        static Request InvalidRequest();
        bool isValid = true;
    public:
        Request();
        std::map<std::string, std::string> headers;
        std::string resource;
        std::string body;
        static Request FromJson(std::string json);
        bool IsValid();
};

void from_json(const nlohmann::json& json, Request& request);