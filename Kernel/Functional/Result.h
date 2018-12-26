#pragma once

#include "functional"
#include <vector>

class Result {
    protected:
        bool isValid;
        const char* errorMessage;
        Result(bool isValid, const char* errorMessage);
    public:
        static Result* Ok();
        static Result* Fail(const char* errorMessage);
        bool IsValid();
        const char* GetErrorMessage();
        Result* OnFail(std::function<void()> callback);
        Result* OnSuccess(std::function<void()> callback);
        Result* OnBoth(std::function<void()> callback);
        static Result* Combine(std::vector<Result*> results);
};


Result::Result(bool isValid, const char* errorMessage) {
    this->isValid = isValid;
    this->errorMessage = errorMessage;
}

Result* Result::Ok() {
    return new Result(true, "");
}

Result* Result::Fail(const char* errorMessage) {
    return new Result(false, errorMessage);
}

bool Result::IsValid() {
    return this->isValid;
}

const char* Result::GetErrorMessage() {
    if(this->isValid) {
        throw  "Cannot get error message from valid result!";
    }

    return this->errorMessage;
}

Result* Result::OnSuccess(std::function<void()> callback) {
    if(this->isValid) {
        callback();
    }

    return this;
}

Result* Result::OnFail(std::function<void()> callback) {
    if(!this->isValid) {
        callback();
    }

    return this;
}

Result* Result::OnBoth(std::function<void()> callback) {
    callback();

    return this;
}

Result* Result::Combine(std::vector<Result*> results) {
    
    for(auto result : results)
    {
        if(!result->IsValid()) {
            return result;
        }
    }

    return Result::Ok();
}