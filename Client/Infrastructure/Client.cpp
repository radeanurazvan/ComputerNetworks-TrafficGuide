#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "string.h"

#include "Client.h"

GenericResult<int>* Client::Connect(const char* address, int port) {
    auto socketResult = this->GetSocket();

    return socketResult->Map<int>([address, port, this](auto socketDescriptor) {
        struct sockaddr_in server;

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(address);
        server.sin_port = htons(port);

        auto connectResult = connect(socketDescriptor, (struct sockaddr *)&server, sizeof(struct sockaddr));
        if (connectResult == -1)
        {
            return GenericResult<int>::Fail("Cannot connect to server");
        }

        return GenericResult<int>::Ok(socketDescriptor);
    });
}

GenericResult<int>* Client::GetSocket() {
    auto socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); 
    if (socketDescriptor == -1)
    {
        return GenericResult<int>::Fail("Cannot create socket!");
    }

    return GenericResult<int>::Ok(socketDescriptor);
}