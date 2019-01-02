#include "Server.h"
#include "Server/Middlewares/Middleware.h"
#include "Kernel/Identity/Guid.h"

class ListeningServer {
    private:
        Server* server;
        int socket;
        int port;
        std::function<Response(int, Guid, Request)> concurrentHandler = [](int clientSocket, Guid connectionId, Request request) { 
            return Response::Ok<std::string>(""); 
        };
        std::function<Guid(int)> connectionIdentityGenerator = [](int clientSocket) { 
            return Guid::EmptyGuid(); 
        };
        Guid AttachClientIdentity(int socket);
    public:
        ListeningServer(Server* server, int socket, int port);
        ListeningServer* WithConnectionIdentityGeneratedBy(std::function<Guid(int)> generator);
        ListeningServer* HandleConcurrentClientsUsing(std::function<Response(int, Guid, Request)> handler);        
        void ConcurrentServe();
};