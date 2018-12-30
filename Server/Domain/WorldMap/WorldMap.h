#pragma once

#include <vector>
#include "WorldStreet.h"
#include "WorldSpeedLimit.h"
#include "WorldCarCrash.h"

#include "../Car/Car.h"

class WorldMap {
    private:
        WorldMap();
        static std::vector<WorldStreet*> streets;
        static std::vector<WorldSpeedLimit*> speedLimits;
        static std::vector<WorldCarCrash*> carCrashes;
        static const int worldStart = 0;
        static const int worldEnd = 500;
    public:
        static std::vector<WorldStreet*> GetStreets();
        static std::vector<WorldSpeedLimit*> GetSpeedLimits();
        static GenericResult<WorldSpeedLimit*>* LimitFor(int position);
        static GenericResult<std::string>* LimitFeedbackFor(Car* car);
        static WorldCarCrash* CrashAt(int position);
        static GenericResult<WorldStreet*>* StreetAt(int position);
};