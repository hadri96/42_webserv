#ifndef MANAGER_HPP
#define MANAGER_HPP

class Client;

class HttpResponse;

class Config;

class Server;

class Manager
{
    public:
    // --- Constructors and Destructor ---
        Manager();
        ~Manager();

    // --- Public Methods ---
        void    run();
        void    initialise(Config& config);
    // ··· Getters and utils ···  
        std::vector<pollfd>&    getPollRequests() { return (pollRequests); };

    private:
    // --- Private Attributes ---
        int                                             server_fd; // fd for listening socket
        std::vector<pollfd>                             pollRequests;
        std::vector<Server>                             serverVect;
        fd_set                                          read_fds; // set of fds to monitor for reading
        fd_set                                          write_fds; // set of fds to monitor for writing

    // --- Private Methods ---


};

#endif
