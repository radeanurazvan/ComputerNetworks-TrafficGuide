#pragma once
#include "Infrastructure/Server.h"

int main() {
    auto server = new Server();
    server->Listen(8080);
}