#include "Kernel/Communication/Response.h"
#include "Kernel/Communication/Request.h"

#include "Server.h"

class ListeningServer {
    private:
        Server* server;
        int socket;
        int port;
        void WriteToClient(int clientSocket, Response message);
        Request ReadFromClient(int clientSocket);
    public:
        ListeningServer(Server* server, int socket, int port);
        void ConcurrentServe();
};