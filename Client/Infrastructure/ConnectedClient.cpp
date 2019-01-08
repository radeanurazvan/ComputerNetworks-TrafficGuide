#include "unistd.h"
#include "ConnectedClient.h"

ConnectedClient::ConnectedClient(int socket) {
    this->socket = socket;

    auto firstResponse = this->ReadResponse();
    firstResponse->OnSuccess([this](Response response) {
        if(!JsonHelper::CanParse<std::map<std::string, std::string>>(response.GetBody())) {
            return;
        }

        auto responseValues = JsonHelper::Parse<std::map<std::string, std::string>>(response.GetBody());
        this->authToken = responseValues["token"];
    });
}

GenericResult<Response>* ConnectedClient::ReadResponse() {
    char serverResponse[255];
    bzero(serverResponse, sizeof(serverResponse));
    if (read(this->socket, serverResponse, 255) <= 0)
    {
        return GenericResult<Response>::Fail("Cannot read from server");
    }

    auto response = JsonHelper::Parse<Response>(std::string(serverResponse));
    return GenericResult<Response>::Ok(response);
}