#include "CarRepository.h"

std::vector<Car*> CarRepository::cars;

std::vector<Car*> CarRepository::GetAll() {
    return cars;
}

GenericResult<Car*>* CarRepository::GetById(Guid id) {
    for(auto car : cars) {
        if(car->GetId() == id) {
            return GenericResult<Car*>::Ok(car);
        }
    }

    return GenericResult<Car*>::Fail("No car found for given id");
}

void CarRepository::Add(Car* car) {
    cars.push_back(car);
}

void CarRepository::Delete(Guid id) {
    for(auto i=0; i< cars.size(); i++) {
        auto car = cars.at(i);
        if(car->GetId() == id) {
            cars.erase(cars.begin() + i);
            break;
        }
    }
}