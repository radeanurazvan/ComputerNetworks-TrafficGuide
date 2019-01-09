#pragma once

#include "unistd.h"
#include "Kernel/Functional/Result.h"
#include "Kernel/Functional/GenericResult.h"
#include "Kernel/Communication/Response.h"
#include "Kernel/Communication/Request.h"
#include "ClientInput.h"

class ConnectedClient {
    private:
        int socket;
        std::string authToken = "";
        std::function<void(std::string)> onTokenAcquired;
        std::map<std::string, std::function<void(ClientInput*)>> commandsDelegates;
        void AcquireToken();
        void ListenForMessages();
        void ListenForCommands();

    public:
        ConnectedClient(int socket);
        void Run();
        GenericResult<Response>* ReadResponse();
        template <class T>
        Result* WriteRequest(std::string resource, T body);
        ConnectedClient* OnTokenAcquired(std::function<void(std::string)> callback);
        template <class T>
        ConnectedClient* WithCommandContract(std::string resourceName, std::function<T(ClientInput*)> contractFactory);
};

template <class T>
Result* ConnectedClient::WriteRequest(std::string resource, T body) {
    Request request;
    
    request.resource = resource;
    request.body = JsonHelper::Serialize<T>(body);
    request.headers["token"] = this->authToken;


    auto requestJson = JsonHelper::Serialize<Request>(request);
    printf("[client] Sending message %s\n\n", requestJson.c_str());
    auto writtenBytes = write(this->socket, requestJson.c_str(), 255);

    if (writtenBytes <= 0)
    {
        return Result::Fail("Cannot write to server");
    }

    printf("[client] Successfully written %d bytes to server\n", writtenBytes);
    return Result::Ok();
}

template <class T>
ConnectedClient* ConnectedClient::WithCommandContract(std::string resourceName, std::function<T(ClientInput*)> contractFactory) {
    std::function<void(ClientInput*)> delegate = [this, contractFactory](ClientInput* input) {
        auto commandContract = contractFactory(input);
        this->WriteRequest<T>(input->GetResource(), commandContract);
    };
    this->commandsDelegates[resourceName] = delegate;

    return this;
}