#ifndef CLIENTCONNECTION_HPP
#define CLIENTCONNECTION_HPP

class ClientConnection
{
    public:
        // Variables:
        int             client_fd;
        bool            is_reading;
        bool            is_writing;
        // HTTPRequest     current_request;
        // HTTPResponse    current_response;
        std::string     read_buffer;
        std::string     write_buffer;

        // Constructors / destructors 

        ClientConnection(int fd) : client_fd(fd), is_reading(true), is_writing(false) {}

        // Methods: 
        
        ssize_t     readFromClient();
        ssize_t     writeToClient();
        void        closeConnection();
        void        handleRequest();
};

#endif
