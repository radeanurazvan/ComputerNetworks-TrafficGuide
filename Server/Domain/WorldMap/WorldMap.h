#pragma once

#include <vector>
#include "WorldStreet.h"
#include "WorldSpeedLimit.h"

class WorldMap {
    private:
        WorldMap();
        static std::vector<WorldStreet*> streets;
        static std::vector<WorldSpeedLimit*> speedLimits;
        static const int worldStart = 0;
        static const int worldEnd = 500;
    public:
        static std::vector<WorldStreet*> GetStreets();
        static std::vector<WorldSpeedLimit*> GetSpeedLimits();
};