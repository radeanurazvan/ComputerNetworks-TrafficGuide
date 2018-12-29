#include "WorldStreet.h"

WorldStreet::WorldStreet(int start, int end, std::string name) {
    this->streetStart = start;
    this->streetEnd = end;
    this->name = name;
}

GenericResult<WorldStreet*>* WorldStreet::Create(int start, int end, std::string name) {
    if(start >= end) {
        return GenericResult<WorldStreet*>::Fail("Cannot create street with inconsistend limits");
    }

    return GenericResult<WorldStreet*>::Ok(new WorldStreet(start, end, name));
}