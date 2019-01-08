#include "stdio.h"
#include "Client.h"

int main() {
    auto client = new Client();
    client->Connect("127.0.0.1", 8080);

    return 0;
}