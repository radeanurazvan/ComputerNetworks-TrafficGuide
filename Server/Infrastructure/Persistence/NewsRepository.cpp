#include "NewsRepository.h"

std::vector<NewsMessage*> NewsRepository::GetAll() {
    return {
        NewsMessage::WeatherMessage("[weather] Enjoy today's sun! 24 degrees."),
        NewsMessage::WeatherMessage("[weather] Be careful on the road. 70% changes of severe rain."),
        NewsMessage::WeatherMessage("[weather] Don't forget your winter tires. It will start snowing soon."),
        NewsMessage::WeatherMessage("[weather] Outside is freezing. You should stay in home today."),
        NewsMessage::WeatherMessage("[weather] Very hot today. Make sure to cover your head."),
        NewsMessage::SportsMessage("[sports] Don't miss tonight's football game! X vs Y in the grand finale."),
        NewsMessage::SportsMessage("[sports] Don't forget to go to the gym!"),
        NewsMessage::SportsMessage("[sports] For a healty lifestyle, workout at least 30 minutes per day."),
        NewsMessage::SportsMessage("[sports] Don't forget to drink your water"),
        NewsMessage::FuelPriceMessage("[fuel] Gas is getting cheap. Wow!"),
        NewsMessage::FuelPriceMessage("[fuel] Gas is getting expensive...again."),
        NewsMessage::FuelPriceMessage("[fuel] Gas got really affordable nowadays."),
        NewsMessage::FuelPriceMessage("[fuel] Gas station 10 miles ahead."),
    };
}