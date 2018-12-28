#pragma once
#include "Kernel/Communication/Response.h"

#include "Server/Resources/Common/ServerResource.h"
#include "Server/Resources/Common/NullRequest.h"

class AuthenticationController: public ServerResource {
    private:
        Response Authenticate(NullRequest* request);
    public:
        std::map<std::string, std::function<Response(ResourceRequest*)>> GetResourceMap();
};