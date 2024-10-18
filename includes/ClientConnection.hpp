#ifndef CLIENTCONNECTION_HPP
#define CLIENTCONNECTION_HPP

class ClientConnection
{
    public:
        // public variables
        std::string     write_buffer; // Stores data that server wants to send to client 
        // std::string     read_buffer; // stores data that client wants to send to server (probably not necessary)

        // Constructors / destructors 
        ClientConnection(int fd) : client_fd(fd), is_reading(true), is_writing(false) {}

        // Methods: 
        
        ssize_t     readFromClient();
        ssize_t     writeToClient();
        void        closeConnection();
        void        handleRequest();
    
    private:
        // Private Variables:
        int             client_fd;
        bool            is_reading;
        bool            is_writing;
        // HTTPRequest     current_request;
        // HTTPResponse    current_response;

};

#endif
