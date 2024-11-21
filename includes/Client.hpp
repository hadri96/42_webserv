#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

/*
This class is the link between Request, Response, and client sockets.
There is one instance of this class per client
Each instance is linked via the ClientMap to its client fd
*/

class Client
{
    public:
    // --- Constructors and Destructor ---
        Client(int fd); //: client_socket(fd), is_reading(true), is_writing(false) {}
        ~Client();

    // --- Public Methods ---
        void                assignRequest(HttpRequest *request_ptr);
        void                assignResponse(HttpResponse *response_ptr);
    
    // ··· Getters and utils ···  
        std::string         getWriteBuffer();
        HttpResponse&       getCurrentResponse();
        HttpRequest&        getCurrentRequest();
        int                 getClientSocket();
    
    private:
    // --- Private Attributes ---
        int             client_socket;
        bool            is_reading;
        bool            is_writing;
        HttpRequest     current_request;
        HttpResponse    current_response;
        std::string     write_buffer; // Stores data that server wants to send to client 
        // std::string     read_buffer; // stores data that client wants to send to server (probably not necessary)

    // --- Private Methods ---
 
};

#endif
