#include "ScaffoldingRequest.h"
#include <cstring>

ScaffoldingRequest::ScaffoldingRequest(std::string resourceMix)
{
    this->controller = std::string(strtok(resourceMix.c_str(), "/"));

    auto method = strtok(NULL, "/");

    if (method == NULL)
    {
        this->method = "";
    } else {
        this->method = method;
    }
}

std::string ScaffoldingRequest::GetController() {
    return this->controller;
}

std::string ScaffoldingRequest::GetMethod() {
    return this->method;
}