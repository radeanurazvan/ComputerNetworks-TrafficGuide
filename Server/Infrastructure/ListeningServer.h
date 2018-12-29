#include "Server.h"
#include "Server/Middlewares/Middleware.h"

class ListeningServer {
    private:
        Server* server;
        int socket;
        int port;
        std::vector<Middleware*> GetMiddlewares(int client);
        bool PassesMiddlewares(int client, Request request);
    public:
        ListeningServer(Server* server, int socket, int port);
        void ConcurrentServe();
};