#pragma once
#include <string>

class Car {
    private:
        Car(std::string id, double speed, int position, double growthFactor);
        std::string id;
        double speed;
        int position;
        double growthFactor;
        static double GetRandomFactor();
        static double GetRandomGrowthFactor();
        int GetDistancePerMinute();

    public:
        static Car* Random(std::string id);
        void Update();
        std::string GetId();
        double GetSpeed();
        int GetPosition();
};