#include "DomainEvents.h"

std::map<const char*, std::vector<std::function<void(DomainEvent*)>>> DomainEvents::subscriptions;
std::map<const char*, std::function<void*(DomainEvent*)>> DomainEvents::uniqueSubscriptions;
