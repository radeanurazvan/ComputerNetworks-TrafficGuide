#pragma once
#include <string>

class Guid {
    private:
        std::string uuid;
        Guid(std::string string);
    public:
        Guid();
        static Guid NewGuid();
        static Guid EmptyGuid();
        bool operator == (Guid other);
        std::string ToString();
};