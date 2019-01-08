#pragma once

#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"
#include "Kernel/Communication/Response.h"
#include "Kernel/Communication/Request.h"

class ConnectedClient {
    private:
        int socket;
        std::string authToken = "";

    public:
        ConnectedClient(int socket);
        GenericResult<Response>* ReadResponse();
        template <class T>
        Result* WriteRequest(std::string resource, T body);
};

template <class T>
Result* ConnectedClient::WriteRequest(std::string resource, T body) {
    Request request;
    
    request.resource = resource;
    request.body = JsonHelper::Serialize<T>(body);
    request.headers["token"] = this->authToken;

    printf("[client] Sending message to %s, value : %s\n\n", request.resource, request.body.c_str());
    auto writtenBytes = write(this->socket, request.body.c_str(), 255);

    if (writtenBytes <= 0)
    {
        return Result::Fail("Cannot write to server");
    }

    printf("[client] Successfully written %d bytes to server", writtenBytes);
    return Result::Ok();
}