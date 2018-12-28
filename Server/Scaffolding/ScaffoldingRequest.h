#pragma once

#include <string>

class ScaffoldingRequest {
    private:
        std::string controller;
        std::string method;
    public:
        ScaffoldingRequest(std::string resourceMix);
        std::string GetController();
        std::string GetMethod();
};