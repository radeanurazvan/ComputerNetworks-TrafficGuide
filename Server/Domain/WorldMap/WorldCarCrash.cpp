#include <ctime>
#include "WorldCarCrash.h"

WorldCarCrash::WorldCarCrash(int position) {
    this->position = position;
    this->createdAt = std::time(0);
}

int WorldCarCrash::GetPosition() {
    return this->position;
}

WorldCarCrash* WorldCarCrash::Create(int position) {
    return new WorldCarCrash(position);
}