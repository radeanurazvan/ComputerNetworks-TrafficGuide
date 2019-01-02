#include "Car.h"
#define CAR_CRASH_DISTANCE_ERROR 50

Car::Car(int socket, int position, double speed) {
    this->id = Guid::NewGuid();

    this->socket = socket;
    this->position = position;
    this->speed = speed;
}

Guid Car::GetId() {
    return this->id;
}

int Car::GetSocket() {
    return this->socket;
}

int Car::GetPosition() {
    return this->position;
}

double Car::GetSpeed() {
    return this->speed;
}

GenericResult<Car*>* Car::Create(int socket, int position, double speed) {
    if(position<0 || speed<0) {
        return GenericResult<Car*>::Fail("Bad car info");
    }

    return GenericResult<Car*>::Ok(new Car(socket, position, speed));
}

Result* Car::Update(int position, double speed) {
    if(position<0 || speed<0) {
        return Result::Fail("Bad car info");
    }

    this->position = position;
    this->speed = speed;

    return Result::Ok();
}

Result* Car::SubscribeTo(NewsType type) {
    for(auto subscription : subscriptions) {
        if(subscription->GetType() == type) {
            return Result::Fail("Already subscribed to this type of news!");
        }
    }

    this->subscriptions.push_back(NewsSubscription::Create(type));
    return Result::Ok();
}

Result* Car::UnsubscribeTo(NewsType type) {
    for(auto i = 0; i < subscriptions.size(); i++) {
        auto subscription = subscriptions.at(i);
        if(subscription->GetType() == type) {
            subscriptions.erase(subscriptions.begin() + i);
            return Result::Ok();
        }
    }

    this->subscriptions.push_back(NewsSubscription::Create(type));
    return Result::Fail("Cannot unsubscribe for a nonexisting subscription!");
}

bool Car::IsInterestedIn(NewsMessage* message) {
    for(auto subscription: subscriptions) {
        if(subscription->GetType() == message->GetType()) {
            return true;
        }
    }

    return false;
}

bool Car::IsCloseTo(WorldCarCrash* crash) {
    auto crashStart = crash->GetPosition() - CAR_CRASH_DISTANCE_ERROR;
    auto crashEnd = crash->GetPosition() + CAR_CRASH_DISTANCE_ERROR;

    return crashStart <= this->GetPosition() && crashEnd >= this->GetPosition();
}