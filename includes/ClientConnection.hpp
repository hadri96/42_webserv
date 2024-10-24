#ifndef CLIENTCONNECTION_HPP
#define CLIENTCONNECTION_HPP

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"


/*
This class is the link between Request, Response, and client sockets.
There is one instance of this class per client
Each instance is linked via the ClientMap to its client fd
*/

class ClientConnection
{
    public:
        // public variables
        std::string     write_buffer; // Stores data that server wants to send to client 
        // std::string     read_buffer; // stores data that client wants to send to server (probably not necessary)

        // Constructors / destructors 
        ClientConnection(int fd); //: client_fd(fd), is_reading(true), is_writing(false) {}
        ~ClientConnection();

        // Methods: 
        ssize_t             readFromClient();
        ssize_t             writeToClient();
        void                closeConnection();
        void                handleRequest();
        void                assignRequest(HTTPRequest *request_ptr);
        void                assignResponse(HTTPResponse *response_ptr);
        HTTPRequest&        getCurrentRequest();
        HTTPResponse&       getCurrentResponse();
    
    private:
        // Private Variables:
        int             client_fd;
        bool            is_reading;
        bool            is_writing;
        HTTPRequest     current_request;
        HTTPResponse    current_response;

};

#endif
