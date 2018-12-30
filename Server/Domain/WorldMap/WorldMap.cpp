#include "WorldMap.h"

WorldMap::WorldMap(){}

std::vector<WorldCarCrash*> WorldMap::carCrashes;

std::vector<WorldStreet*> WorldMap::streets = {
    WorldStreet::Create(0, 106, "Strada Pacurari")->GetValue(),
    WorldStreet::Create(106, 115, "Pasaj Octav Bancila")->GetValue(),
    WorldStreet::Create(115, 173, "Soseaua Nationala")->GetValue(),
    WorldStreet::Create(173, 195, "Strada Sarmisegetuza")->GetValue(),
    WorldStreet::Create(195, 235, "Strada Cerna")->GetValue(),
    WorldStreet::Create(235, 246, "Strada Crisului")->GetValue(),
    WorldStreet::Create(246, 339, "Strada Petru Schiopu")->GetValue(),
    WorldStreet::Create(339, 365, "Calea Galata")->GetValue(),
    WorldStreet::Create(365, 377, "Strada Vasile A. Urechila")->GetValue(),
    WorldStreet::Create(377, 378, "Statie Taxi Amanet")->GetValue(),
    WorldStreet::Create(378, 432, "Strada Fluturilor")->GetValue(),
    WorldStreet::Create(432, 488, "Strada Alunis")->GetValue(),
    WorldStreet::Create(488, 500, "Strada Roadelor")->GetValue()
};

std::vector<WorldSpeedLimit*> WorldMap::speedLimits = {
    WorldSpeedLimit::Create(0, 46, City)->GetValue(),
    WorldSpeedLimit::Create(46, 81, OutsideCity)->GetValue(),
    WorldSpeedLimit::Create(81, 91, OutsideCity)->GetValue(),
    WorldSpeedLimit::Create(91, 127, City)->GetValue(),
    WorldSpeedLimit::Create(127, 134, CityHighSpeedLane)->GetValue(),
    WorldSpeedLimit::Create(134, 145, CityHighSpeedLane)->GetValue(),
    WorldSpeedLimit::Create(145, 150, City)->GetValue(),
    WorldSpeedLimit::Create(150, 174, Crosswalk)->GetValue(),
    WorldSpeedLimit::Create(174, 194, City)->GetValue(),
    WorldSpeedLimit::Create(194, 195, Crosswalk)->GetValue(),
    WorldSpeedLimit::Create(195, 205, Crosswalk)->GetValue(),
    WorldSpeedLimit::Create(205, 219, City)->GetValue(),
    WorldSpeedLimit::Create(219, 247, CityHighSpeedLane)->GetValue(),
    WorldSpeedLimit::Create(247, 275, City)->GetValue(),
    WorldSpeedLimit::Create(275, 297, City)->GetValue(),
    WorldSpeedLimit::Create(297, 329, City)->GetValue(),
    WorldSpeedLimit::Create(329, 342, CityHighSpeedLane)->GetValue(),
    WorldSpeedLimit::Create(342, 370, OutsideCity)->GetValue(),
    WorldSpeedLimit::Create(370, 420, OutsideCity)->GetValue(),
    WorldSpeedLimit::Create(420, 430, Highway)->GetValue(),
    WorldSpeedLimit::Create(430, 500, Highway)->GetValue(),
};

std::vector<WorldStreet*> WorldMap::GetStreets() {
    return streets;
}

std::vector<WorldSpeedLimit*> WorldMap::GetSpeedLimits() {
    return speedLimits;
}

GenericResult<WorldSpeedLimit*>* WorldMap::LimitFor(int position) {
    for(auto limit: speedLimits) {
        if(limit->ContainsPosition(position)) {
            return GenericResult<WorldSpeedLimit*>::Ok(limit);
        }
    }

    return GenericResult<WorldSpeedLimit*>::Fail("No limit found for position");
}

GenericResult<std::string>* WorldMap::LimitFeedbackFor(Car* car) {
    auto limitOrNothing = LimitFor(car->GetPosition());
    return limitOrNothing->Map<std::string>([car](WorldSpeedLimit* limit) {
        char message[100];
        if(car->GetSpeed() > limit->GetValue()) {
            sprintf(message, "[DANGER] Driving above speed limit! Please slow down to %d for the current road", limit->GetValue());
        } else {
            sprintf(message, "[INFO] Current speed is below speed limit. Please keep your speed below %d", limit->GetValue());
        }
        
        return GenericResult<std::string>::Ok(std::string(message));
    });
}

WorldCarCrash* WorldMap::CrashAt(int position) {
    auto crash = WorldCarCrash::Create(position);
    carCrashes.push_back(crash);

    return crash;
}

GenericResult<WorldStreet*>* WorldMap::StreetAt(int position) {
    for(auto street: streets) {
        if(street->ContainsPosition(position)){
            return GenericResult<WorldStreet*>::Ok(street);
        }
    }

    return GenericResult<WorldStreet*>::Fail("No street found for given position");
}