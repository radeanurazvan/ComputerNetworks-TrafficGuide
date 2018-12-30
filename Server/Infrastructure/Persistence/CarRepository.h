#pragma once

#include <vector>
#include "Kernel/Functional/GenericResult.h"
#include "Server/Domain/Car/Car.h"

class CarRepository {
    private:
        static std::vector<Car*> cars;
    public:
        static std::vector<Car*> GetAll();
        static std::vector<Car*> Find(std::function<bool(Car*)> eval);
        static GenericResult<Car*>* GetById(Guid id);
        static void Add(Car* car);
        static void Delete(Guid id);
        static void DeleteWhere(std::function<bool(Car*)> eval);
};