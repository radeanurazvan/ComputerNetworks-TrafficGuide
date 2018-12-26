#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "string.h"

#include "Server.h"

Result* Server::Listen(int port) {
    printf("Listening to %d...", port);

    auto socketResult = this->CreateSocket();
    auto bindResult = this->Bind(socketResult, port);
    auto listenResult = this->Listen(socketResult);

    auto results = std::vector<Result*>({socketResult->ToSampleResult(), bindResult, listenResult});
    auto finalResult = Result::Combine(results);
    return finalResult
        ->OnFail([finalResult]() {
            printf("%s", finalResult->GetErrorMessage());
        });
}

GenericResult<int>* Server::CreateSocket() {
    auto socketResult = socket (AF_INET, SOCK_STREAM, 0);
    if (socketResult == -1)
    {
        return GenericResult<int>::Fail("Socket error. Could not create socket");
    }

    int on=1;
    setsockopt(socketResult,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    return GenericResult<int>::Ok(socketResult);
}

Result* Server::Bind(GenericResult<int>* socketResult, int port) {
    if(!socketResult->IsValid()) {
        return socketResult->ToSampleResult();
    }

    struct sockaddr_in server;

    bzero (&server, sizeof (server));
    
    server.sin_family = AF_INET;	
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons(port);
    
    if (bind (socketResult->GetValue(), (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
        return Result::Fail("Bind error");
    }

    return Result::Ok();
}

Result* Server::Listen(GenericResult<int>* socketResult) {
    if(!socketResult->IsValid()) {
        return socketResult->ToSampleResult();
    }

    if (listen (socketResult->GetValue(), 2) == -1)
    {
        return Result::Fail("Listen error!");
    }

    return Result::Ok();
}