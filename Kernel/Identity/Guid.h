#pragma once
#include <string>

class Guid {
    private:
        std::string uuid;
        Guid(std::string string);
    public:
        static Guid NewGuid();
        bool operator == (Guid other);
        std::string ToString();
};