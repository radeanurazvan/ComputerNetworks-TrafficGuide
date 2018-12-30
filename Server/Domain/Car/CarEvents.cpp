#include "CarEvents.h"
#include "Events/CarCrashReportedEvent.h"
#include "Events/UnreachableCarDetectedEvent.h"
#include "EventHandlers/UnreachableCarDetectedEventHandler.h"
#include "EventHandlers/CarCrashReportedEventHandler.h"
#include "Server/Events/DomainEvents.h"


void CarEvents::Setup() {
    DomainEvents::Subscribe<UnreachableCarDetectedEvent>([](DomainEvent* event) {
        auto castedEvent = (UnreachableCarDetectedEvent*) event;
        auto handler = new UnreachableCarDetectedEventHandler();
        handler->Handle(castedEvent);
    });

    DomainEvents::Subscribe<CarCrashReportedEvent>([](DomainEvent* event) {
        auto castedEvent = (CarCrashReportedEvent*) event;
        auto handler = new CarCrashReportedEventHandler();
        handler->Handle(castedEvent);
    });
}