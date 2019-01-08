#include "Client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


Result* Client::Connect(const char* address, int port) {
    auto socketResult = this->GetSocket();
    if(!socketResult->IsValid()) {
        return socketResult->ToSampleResult();
    }

    auto socket = socketResult->GetValue();
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(address);
    server.sin_port = htons(port);

    auto connectResult = connect(socket, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (connectResult == -1)
    {
        return Result::Fail("Cannot connect to server");
    }
    
    return Result::Ok();
}

GenericResult<int>* Client::GetSocket() {
    auto socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); 
    if (socketDescriptor == -1)
    {
        return GenericResult<int>::Fail("Cannot create socket!");
    }

    return GenericResult<int>::Ok(socketDescriptor);
}