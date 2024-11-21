#ifndef SERVER_HPP
#define SERVER_HPP

class Config;

class Client;

class Manager;

class HttpResponse;

class Server
{
    public:
    // --- Public Attributes ---

    // --- Constructors and Destructor ---
        Server(Manager* manager);
        ~Server();

    // --- Public Methods ---
        void    bindSocket();
        void    listenOnPort();
        void    applyConfig(Config& config, int i) 
        {
            port = config.getPort(i);
        };

    // ··· Getters,setters and utils ···  
        int                             getServerSock() const {return (serverSocket);};
        void                            setServerSock(int sock) { serverSocket = sock; };
        Client*                         getClientFromSocket(int clientSocket);

    // ··· Setup Methods ··· 
        void    connectNewClientToServer();
        void    closeClient(std::size_t *i, std::string message);

    // ··· HTTP handling Methods ··· 
        void    handleClientRead(std::size_t *i);
        void    handleClientWrite(std::size_t *i);
        void    sendResponseBuffer(std::size_t *i, HttpResponse &response);


    private:
    // --- Private Attributes ---
        int                         serverSocket;
        int                         port;
        std::vector<Client>         clientVect;
        Manager*                    manager;

    // --- Private Methods ---
 
};

#endif
