#include "WorldSpeedLimit.h"

WorldSpeedLimit::WorldSpeedLimit(int start, int end, SpeedLimit value) {
    this->limitStart = start;
    this->limitEnd = end;
    this->value = value;
}

GenericResult<WorldSpeedLimit*>* WorldSpeedLimit::Create(int start, int end, SpeedLimit value) {
    if(start >= end) {
        return GenericResult<WorldSpeedLimit*>::Fail("Cannot create speed limit with inconsistent range");
    }

    return GenericResult<WorldSpeedLimit*>::Ok(new WorldSpeedLimit(start, end, value));
}

bool WorldSpeedLimit::ContainsPosition(int position) {
    return limitStart <= position && limitEnd >= position;
}

int WorldSpeedLimit::GetValue() {
    return this->value; 
}