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
        Response ResponseFromResult(GenericResult<T>* result, int code = BadRequest);
        Response ResponseFromResult(Result* result, int code = BadRequest) {
            if(code != BadRequest) {
                return Response::Custom(result->GetErrorMessage(), code);
            }

            if(!result->IsValid()) {
                return Response::BadRequest(result->GetErrorMessage());
            }

            return Response::Ok<std::string>("");
        }
};

template <class T>
Response ServerResource::ResponseFromResult(GenericResult<T>* result, int code = BadRequest) {
    if(!result->IsValid()) {
        return Response::Custom(result->GetErrorMessage(), code);
    }

    return Response::Ok<T>(result->GetValue());
}