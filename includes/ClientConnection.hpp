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
    // --- Constructors and Destructor ---
        ClientConnection(int fd); //: client_socket(fd), is_reading(true), is_writing(false) {}
        ~ClientConnection();

    // --- Public Methods ---
        void                assignRequest(HTTPRequest *request_ptr);
        void                assignResponse(HTTPResponse *response_ptr);
    
    // ··· Getters and utils ···  
        std::string         getWriteBuffer();
        HTTPResponse&       getCurrentResponse();
        HTTPRequest&        getCurrentRequest();
        int                 getClientSocket();
    
    private:
    // --- Private Attributes ---
        int             client_socket;
        bool            is_reading;
        bool            is_writing;
        HTTPRequest     current_request;
        HTTPResponse    current_response;
        std::string     write_buffer; // Stores data that server wants to send to client 
        // std::string     read_buffer; // stores data that client wants to send to server (probably not necessary)

    // --- Private Methods ---
 
};

#endif
