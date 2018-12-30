#pragma once

#include <string>
#include "NewsType.h"

class NewsMessage {
    private:
        NewsMessage(NewsType type, std::string message);
        NewsType type;
        std::string message;
    public:
        static NewsMessage* WeatherMessage(std::string message);
        static NewsMessage* SportsMessage(std::string message);
        static NewsMessage* FuelPriceMessage(std::string message);
        NewsType GetType();
        std::string GetMessage();
};