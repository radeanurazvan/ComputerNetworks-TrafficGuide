#include "Server.h"

class ListeningServer {
    private:
        Server* server;
        int socket;
        int port;
    public:
        ListeningServer(Server* server, int socket, int port);
        void ConcurrentServe();
};