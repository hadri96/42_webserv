#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP


class EventLoop
{
    public:
        // Variables 
        int                                             server_fd; // fd for listening socket
        std::unordered_map<int, ClientConnection>       clients; // client fds mapped to client objs
        fd_set                                          read_fds; // set of fds to mnitor for reading
        fd_set                                          write_fds; // set of fds to mnitor for writing

        // Constructors / destructors
        Eventloop(int server_fd) : server_fd(server_fd) {}

        // Methods:
        void    run();
        void    acceptClient();
        void    handleReadEvent();
        void    handleWriteEvent();
        void    closeClient(int client_fd);
        void    updateFdSets();
}

#endif