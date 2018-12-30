#pragma once

#include <map>
#include <thread>
#include <functional>
#include <vector>
#include "DomainEvent.h"

class DomainEvents {
    private:
        static std::map<const char*, std::vector<std::function<void(DomainEvent*)>>> subscriptions;
        DomainEvents();
    public:
        template <class T>
        static void Subscribe(std::function<void(DomainEvent*)> handler);
        template <class T>
        static void Publish(T* event);
};

template <class T>
void DomainEvents::Subscribe(std::function<void(DomainEvent*)> handler) {
    printf("[server] Subscribing for %s\n", typeid(T).name());

    auto eventKey = typeid(T).name();
    subscriptions[eventKey].push_back(handler);
}

template <class T>
void DomainEvents::Publish(T* event) {
    printf("[server] Publishing for %s\n", typeid(T).name());
    
    auto handlingThread = std::thread([event]() {
        auto subscribers = subscriptions[typeid(T).name()];
        for(auto subscriber : subscribers) {
            subscriber(event);
        }
    });        
    handlingThread.detach();
}