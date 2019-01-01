#include "CarEvents.h"
#include "Events/CarCrashReportedEvent.h"
#include "Events/UnreachableCarDetectedEvent.h"
#include "Events/CarConnectedEvent.h"
#include "EventHandlers/UnreachableCarDetectedEventHandler.h"
#include "EventHandlers/CarCrashReportedEventHandler.h"
#include "EventHandlers/CarConnectedEventHandler.h"
#include "Server/Events/DomainEvents.h"


void CarEvents::Setup() {
    DomainEvents::SubscribeUnique<CarConnectedEvent, CarConnectedEventHandler>();
    DomainEvents::Subscribe<UnreachableCarDetectedEvent, UnreachableCarDetectedEventHandler>();
    DomainEvents::Subscribe<CarCrashReportedEvent, CarCrashReportedEventHandler>();
    
    // DomainEvents::Subscribe<UnreachableCarDetectedEvent>([](DomainEvent* event) {
    //     auto castedEvent = (UnreachableCarDetectedEvent*) event;
    //     auto handler = new UnreachableCarDetectedEventHandler();
    //     handler->Handle(castedEvent);
    // });

    // DomainEvents::Subscribe<CarCrashReportedEvent>([](DomainEvent* event) {
    //     auto castedEvent = (CarCrashReportedEvent*) event;
    //     auto handler = new CarCrashReportedEventHandler();
    //     handler->Handle(castedEvent);
    // });
}