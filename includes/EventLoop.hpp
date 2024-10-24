#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

class ClientConnection;

class HTTPResponse;

class EventLoop
{
    public:
        
        // Constructors / destructors
        EventLoop(int port) : port(port) {}
        ~EventLoop() {};

        // Methods:
        void    setupServer();
        void    bindSocket();
        void    listenOnPort();
        void    connectNewClientToServer();
        void    closeClient(std::size_t *i, std::string message);
        void    handleClientRead(std::size_t *i);
        void    handleClientWrite(std::size_t *i);
        void    sendResponseBuffer(std::size_t *i, HTTPResponse &response);
        void    run();
    
    private: 
        // Variables 
        int                                             server_fd; // fd for listening socket
        int                                             port;
        std::map<int, ClientConnection>                 clientMap; // client fds mapped to client request objs
        std::vector<pollfd>                             pollRequests;
        fd_set                                          read_fds; // set of fds to mnitor for reading
        fd_set                                          write_fds; // set of fds to mnitor for writing

};

#endif
