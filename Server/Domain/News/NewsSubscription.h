#pragma once

#include "NewsType.h"

class NewsSubscription {
    private:
        NewsSubscription(NewsType type);
        NewsType type;
    public:
        static NewsSubscription* Create(NewsType type);
        NewsType GetType();
};