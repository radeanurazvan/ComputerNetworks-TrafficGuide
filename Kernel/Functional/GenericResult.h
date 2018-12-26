#pragma once

#include "functional"
#include "Kernel/Functional/Result.h"

template <class T>
class GenericResult {
    private:
        T value;
        bool isValid;
        const char* errorMessage; 

        GenericResult(T value, bool isValid, const char* errorMessage);
    public:
        static GenericResult<T>* Ok(T value);
        static GenericResult<T>* Fail(const char* errorMessage);
        T GetValue();
        bool IsValid();
        const char* GetErrorMessage();
        GenericResult<T>* OnSuccess(std::function<void(T)> callback);
        GenericResult<T>* OnFail(std::function<void()> callback);
        GenericResult<T>* OnBoth(std::function<void()> callback);
        Result* ToSampleResult();
};

template <class T>
GenericResult<T>::GenericResult(T value, bool isValid, const char* errorMessage) {
    this->value = value;
    this->isValid = isValid;
    this->errorMessage = errorMessage;
}

template <class T>
GenericResult<T>* GenericResult<T>::Ok(T value) {
    return new GenericResult<T>(value, true, "");
}

template <class T>
GenericResult<T>* GenericResult<T>::Fail(const char* errorMessage) {
    return new GenericResult<T>(NULL, false, errorMessage);
}

template <class T>
bool GenericResult<T>::IsValid() {
    return this->isValid;
}

template <class T>
const char* GenericResult<T>::GetErrorMessage() {
    if(this->isValid) {
        throw "Cannot get error message from valid result!";
    }
    
    return this->errorMessage;
}

template <class T>
T GenericResult<T>::GetValue() {
    if(!this->isValid) {
        throw "Cannot get value from invalid result!";
    }

    return this->value;
}

template <class T>
GenericResult<T>* GenericResult<T>::OnSuccess(std::function<void(T)> callback) {
    if(this->isValid) {
        callback(this.value);
    }

    return this;
}

template <class T>
GenericResult<T>* GenericResult<T>::OnFail(std::function<void()> callback) {
    if(!this->isValid) {
        callback();
    }

    return this;
}

template <class T>
GenericResult<T>* GenericResult<T>::OnBoth(std::function<void()> callback) {
    callback();

    return this;
}

template <class T>
Result* GenericResult<T>::ToSampleResult() {
    if(this->IsValid()) {
        return Result::Ok();
    }

    return Result::Fail(this->GetErrorMessage());
}