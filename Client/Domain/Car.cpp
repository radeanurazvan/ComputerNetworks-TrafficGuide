#include "time.h"
#include "Car.h"

Car::Car(std::string id, double speed, int position, double growthFactor) {
    this->id = id;
    this->speed = speed;
    this->position = position;
    this->growthFactor = growthFactor;
}

Car* Car::Random(std::string id) {
    srand(time(0));

    auto position = rand() % 500;
    auto speed = rand() % 200;
    auto growthFactor = GetRandomGrowthFactor();

    return new Car(id, speed, position, growthFactor);
}

void Car::Update() {
    srand(time(0));

    auto distanceGained = this->GetDistancePerMinute();
    this->position += distanceGained;
    if(this->position >= 500) {
        this->position = 1;
    }

    auto factor = this->growthFactor;
    auto positivityFactor = GetRandomFactor();
    if(positivityFactor > 0.55) {
        factor *= -1;
    }
    this->speed += factor * speed;

    this->growthFactor = this->GetRandomGrowthFactor();
}

int Car::GetDistancePerMinute() {
    return this->speed / 60;
}

double Car::GetRandomFactor() {
    return (double)rand() / RAND_MAX;
}

double Car::GetRandomGrowthFactor() {
    return (double)rand() / RAND_MAX / 1.5;
}

std::string Car::GetId() {
    return this->id;
}

int Car::GetPosition() {
    return this->position;
}

double Car::GetSpeed() {
    return this->speed;
}