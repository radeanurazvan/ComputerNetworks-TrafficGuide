#pragma once

#include <map>
#include <string>
#include <functional>

#include "Kernel/Communication/Response.h"
#include "ControllerResourceAdapter.h"

class ServerResource {
    public:
        virtual std::map<std::string, ControllerResourceAdapter*> GetAdaptersMap() = 0;
        template <class T>
        Response ResponseFromResult(GenericResult<T>* result);
        Response ResponseFromResult(Result* result) {
            if(!result->IsValid()) {
                return Response::BadRequest(result->GetErrorMessage());
            }

            return Response::Ok<std::string>("");
        }
};

template <class T>
Response ServerResource::ResponseFromResult(GenericResult<T>* result) {
    if(!result->IsValid()) {
        return Response::BadRequest(result->GetErrorMessage());
    }

    return Response::Ok<T>(result->GetValue());
}