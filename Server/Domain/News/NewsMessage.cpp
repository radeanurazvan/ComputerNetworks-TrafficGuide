#include "NewsMessage.h"

NewsMessage::NewsMessage(NewsType type, std::string message) {
    this->type = type;
    this->message = message;
}

NewsMessage* NewsMessage::WeatherMessage(std::string message) {
    return new NewsMessage(Weather, message);
}

NewsMessage* NewsMessage::SportsMessage(std::string message) {
    return new NewsMessage(Sports, message);
}


NewsMessage* NewsMessage::FuelPriceMessage(std::string message) {
    return new NewsMessage(FuelPrice, message);
}

NewsType NewsMessage::GetType() {
    return this->type;
}

std::string NewsMessage::GetMessage() {
    return this->message;
}