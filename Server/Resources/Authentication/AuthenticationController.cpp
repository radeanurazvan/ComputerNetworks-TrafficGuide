#include "AuthenticationController.h"

Response AuthenticationController::Authenticate(NullRequest* request) {
    return Response::Unauthorized();
}

std::map<std::string, std::function<Response(ResourceRequest*)>> AuthenticationController::GetResourceMap() {
    std::map<std::string, std::function<Response(ResourceRequest*)>> resourceMap;

    resourceMap["authenticate"] = [this](ResourceRequest* request) {
        return this->Authenticate((NullRequest*)request);
    };

    return resourceMap;
}