#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

class EventLoop
{
    public:
        // Variables 
        int                                             server_fd; // fd for listening socket
        int                                             port;
        std::map<int, std::string>                      clientMap; // client fds mapped to client request objs
        std::vector<pollfd>                             pollfds;
        fd_set                                          read_fds; // set of fds to mnitor for reading
        fd_set                                          write_fds; // set of fds to mnitor for writing

        // Constructors / destructors
        EventLoop(int port) : port(port) {}

        // Methods:
        void    setupServer();
        void    run();
        void    acceptClient();
        void    handleReadEvent();
        void    handleWriteEvent();
        void    closeClient(int client_fd);
        void    updateFdSets();
};

#endif
