#include "ListenOptions.h"

ListenOptions::ListenOptions(int socket, int port) {
    this->socket = socket;
    this->port = port;
}

int ListenOptions::GetSocket() {
    return this->socket;
}

int ListenOptions::GetPort() {
    return this->port;
}