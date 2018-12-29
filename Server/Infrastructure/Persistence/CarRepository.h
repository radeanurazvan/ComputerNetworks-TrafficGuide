#pragma once

#include <vector>
#include "Kernel/Functional/GenericResult.h"
#include "Server/Domain/Car/Car.h"

class CarRepository {
    private:
        static std::vector<Car*> cars;
    public:
        static std::vector<Car*> GetAll();
        static GenericResult<Car*>* GetById(Guid id);
        static void Add(Car* car);
        static void Delete(Guid id);
};