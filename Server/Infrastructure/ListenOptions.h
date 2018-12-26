#pragma once

class ListenOptions {
    private:
        int socket;
        int port;
    public:
        ListenOptions(int socket, int port);
        int GetSocket();
        int GetPort();
};