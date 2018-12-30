#pragma once

class WorldCarCrash {
    private:
        WorldCarCrash(int position);
        int position;
        int createdAt;
    public:
        static WorldCarCrash* Create(int position);
        int GetPosition();
};