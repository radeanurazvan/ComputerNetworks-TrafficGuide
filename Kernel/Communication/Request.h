#pragma once
#include <string>
#include "../3rdParties/json/single_include/nlohmann/json.hpp"

class Request {
    private:
        bool isValid = true;
    public:
        Request();
        std::string resource;
        std::string body;
        static Request FromJson(std::string json);
        bool IsValid();
};

void from_json(const nlohmann::json& json, Request& request);