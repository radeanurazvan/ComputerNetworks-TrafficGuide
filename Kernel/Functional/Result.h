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