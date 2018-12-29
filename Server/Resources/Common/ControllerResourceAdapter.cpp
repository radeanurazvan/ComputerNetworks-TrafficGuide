#include "ControllerResourceAdapter.h"

ControllerResourceAdapter::ControllerResourceAdapter(std::function<Response(ResourceRequest*)> controllerMethod) {
    this->controllerMethod = controllerMethod;
}

ControllerResourceAdapter* ControllerResourceAdapter::NotGuardedByAuthorization() {
    this->needsAuthorization = false;

    return this;
}

bool ControllerResourceAdapter::NeedsAuthorization() {
    return this->needsAuthorization;
}

GenericResult<Response>* ControllerResourceAdapter::GetResponse(std::string request) {
    auto resourceRequestOrFail = this->AdaptRequest(request);
    
    return resourceRequestOrFail->Map<Response>([&](ResourceRequest* request) {
        return GenericResult<Response>::Ok(this->controllerMethod(request));
    });
}