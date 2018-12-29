#pragma once

#include <vector>
#include <string>

#include "Kernel/Functional/GenericResult.h"

class WorldStreet {
    private:
        WorldStreet(int start, int end, std::string name);
        int streetStart;
        int streetEnd;
        std::string name;
    public:
        static GenericResult<WorldStreet*>* Create(int start, int end, std::string name);
        bool ContainsPosition(int position);
};