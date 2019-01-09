#include "unistd.h"
#include "thread"
#include <iostream>
#include "ConnectedClient.h"
#include "ClientInput.h"

ConnectedClient::ConnectedClient(int socket) {
    this->socket = socket;
}

GenericResult<Response>* ConnectedClient::ReadResponse() {
    std::string serverResponse = "";

    char responseChar[1];
    bzero(responseChar, sizeof(responseChar));
    int readBytes;
    while((readBytes = read(this->socket, &responseChar, 1)) >= 0) {
        serverResponse += std::string(responseChar);
        auto hasStartOfFile = serverResponse.find("<SOF>") != -1;
        auto hasEndOfFile = serverResponse.find("<EOF>") != -1;

        if(hasStartOfFile && hasEndOfFile) {
            serverResponse.erase(0, 5);
            serverResponse.erase(serverResponse.size() - 5, 5);

            auto response = JsonHelper::Parse<Response>(std::string(serverResponse));
            return GenericResult<Response>::Ok(response);
        }
    }

    return GenericResult<Response>::Fail("Cannot read from server");
}

ConnectedClient* ConnectedClient::OnTokenAcquired(std::function<void(std::string)> onTokenAcquired) {
    this->onTokenAcquired = onTokenAcquired;
    return this;
}

void ConnectedClient::Run() {
    this->AcquireToken();
    this->ListenForCommands();
    this->ListenForMessages();
}

void ConnectedClient::AcquireToken() {
    auto firstResponse = this->ReadResponse();
    firstResponse->OnSuccess([this](Response response) {
        if(!JsonHelper::CanParse<std::map<std::string, std::string>>(response.GetBody())) {
            return;
        }

        auto responseValues = JsonHelper::Parse<std::map<std::string, std::string>>(response.GetBody());
        this->authToken = responseValues["token"];

        this->onTokenAcquired(this->authToken);
    });
}

void ConnectedClient::ListenForMessages() {
    auto messagesThread = std::thread([this]() {
        while(true) {
            auto messageResult = this->ReadResponse();
            messageResult->OnSuccess([](Response response) {
                printf("[client] Received message:\n %s\n\n", response.GetBody().c_str());
            });
        }
    });
    messagesThread.join();
}

void ConnectedClient::ListenForCommands() {
    auto commandsThread = std::thread([this]() {
        while(true) {
            char commandInput[1000];
            std::cin.getline(commandInput, 1000);

            auto clientInputResult = ClientInput::Create(std::string(commandInput));
            clientInputResult
                ->OnSuccess([this](ClientInput* clientInput) {
                    if(this->commandsDelegates.find(clientInput->GetResource()) != this->commandsDelegates.end()) {
                        auto delegate = this->commandsDelegates[clientInput->GetResource()];
                        delegate(clientInput);
                    }
                })
                ->OnFail([clientInputResult]() {
                    printf("[client] %s\n", clientInputResult->GetErrorMessage());
                });
        }
    });
    commandsThread.detach();
}
