#pragma once

#include <map>
#include <thread>
#include <functional>
#include <vector>
#include "DomainEvent.h"

class DomainEvents {
    private:
        static std::map<const char*, std::vector<std::function<void(DomainEvent*)>>> subscriptions;
        static std::map<const char*, std::function<void*(DomainEvent*)>> uniqueSubscriptions;
        DomainEvents();
    public:
        template <class T>
        static void Subscribe(std::function<void(DomainEvent*)> handler);
        template <class TEvent, class THandler>
        static void Subscribe();
        template <class TEvent, class THandler>
        static void* SubscribeUnique();
        template <class T>
        static void Publish(T* event);
        template <class TEvent, class TResult>
        static TResult PublishUnique(TEvent* event);
};

template <class T>
void DomainEvents::Subscribe(std::function<void(DomainEvent*)> handler) {
    auto eventName = typeid(T).name();
    printf("[server] Subscribing for %s\n", eventName);

    auto eventKey = eventName;
    subscriptions[eventKey].push_back(handler);
}

template <class TEvent, class THandler>
void DomainEvents::Subscribe() {
    printf("[server] Subscribing for %s\n", typeid(TEvent).name());

    auto handler = [](DomainEvent* event){
        auto castedEvent = (TEvent*) event;
        auto handler = new THandler();
        handler->Handle(castedEvent);
    };

    auto eventKey = typeid(TEvent).name();
    subscriptions[eventKey].push_back(handler);
}

template <class TEvent, class THandler>
void* DomainEvents::SubscribeUnique() {
    printf("[server] Subscribing for %s\n", typeid(TEvent).name());

    auto handler = [](DomainEvent* event){
        auto castedEvent = (TEvent*) event;
        auto handler = new THandler();
        auto handlerResult = handler->Handle(castedEvent);
        auto resultVoidReference = (void*) (&handlerResult); 
        return resultVoidReference;
    };

    auto eventKey = typeid(TEvent).name();
    uniqueSubscriptions[eventKey] = handler;
}

template <class T>
void DomainEvents::Publish(T* event) {
    auto eventName = typeid(T).name();
    printf("[server] Publishing for %s\n", eventName);
    
    auto handlingThread = std::thread([event, eventName]() {
        auto subscribers = subscriptions[eventName];
        for(auto subscriber : subscribers) {
            subscriber(event);
        }
    });        
    handlingThread.detach();
}

template <class TEvent, class TResult>
TResult DomainEvents::PublishUnique(TEvent* event) {
    auto eventName = typeid(TEvent).name();
    printf("[server] Publishing for %s\n", eventName);

    auto subscriber = uniqueSubscriptions[eventName];
    auto subscriberResult = subscriber(event);
    TResult* castedSubscriberResult = subscriberResult;
    auto finalResult = *castedSubscriberResult;
    return finalResult;
}