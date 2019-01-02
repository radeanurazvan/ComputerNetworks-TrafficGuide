#pragma once
#include <string>

class Guid {
    private:
        std::string uuid;
    public:
        Guid(std::string string);
        Guid();
        static Guid NewGuid();
        static Guid EmptyGuid();
        bool operator == (Guid other);
        std::string ToString() const;
};