#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

class ClientConnection;

class HTTPResponse;

class EventLoop
{
    public:
    // --- Constructors and Destructor ---
        EventLoop(int port) : port(port) {}
        ~EventLoop() {};

    // --- Public Methods ---
        void    setupServer();
        void    run();

    private:
    // --- Private Attributes ---
        int                                             server_fd; // fd for listening socket
        int                                             port; // comes from config file
        std::vector<pollfd>                             pollRequests;
        std::vector<ClientConnection>                   clientVect;
        // std::vector<ServerConfig>                    ServerBlockVect;
        fd_set                                          read_fds; // set of fds to monitor for reading
        fd_set                                          write_fds; // set of fds to monitor for writing

    // --- Private Methods ---

    // ··· Getters and utils ···  
        ClientConnection*   getClientFromSocket(int client_socket);

    // ··· Setup Methods ··· 
        void    bindSocket();
        void    listenOnPort();
        void    connectNewClientToServer();
        void    closeClient(std::size_t *i, std::string message);

    // ··· HTTP handling Methods ··· 
        void    handleClientRead(std::size_t *i);
        void    handleClientWrite(std::size_t *i);
        void    sendResponseBuffer(std::size_t *i, HTTPResponse &response);


};

#endif
