#include "NewsSubscription.h"

NewsSubscription::NewsSubscription(NewsType type) {
    this->type = type;
}

NewsSubscription* NewsSubscription::Create(NewsType type) {
    return new NewsSubscription(type);
}

NewsType NewsSubscription::GetType() {
    return this->type;
}