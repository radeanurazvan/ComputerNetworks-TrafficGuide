#pragma once

#include "Kernel/Functional/GenericResult.h"

enum SpeedLimit {
    Crosswalk = 30,
    City = 50,
    CityHighSpeedLane = 70,
    OutsideCity = 100,
    Highway = 130 
};

class WorldSpeedLimit {
    private:
        WorldSpeedLimit(int start, int end, SpeedLimit value);
        int limitStart;
        int limitEnd;
        SpeedLimit value;
    public:
        static GenericResult<WorldSpeedLimit*>* Create(int start, int end, SpeedLimit value);
        bool ContainsPosition(int position);
        int GetValue();
};