#include "../../includes/webserv.hpp"

ClientConnection::ClientConnection(int fd) : client_fd(fd), is_reading(true), is_writing(false) {}

ClientConnection::~ClientConnection() {}

void        ClientConnection::assignRequest(HTTPRequest *request_ptr)
{
    current_request = *request_ptr;
}

void        ClientConnection::assignResponse(HTTPResponse *response_ptr)
{
    current_response = *response_ptr;
}


HTTPRequest&         ClientConnection::getCurrentRequest()
{
    return (this->current_request);
}

HTTPResponse&        ClientConnection::getCurrentResponse()
{
    return (this->current_response);
}
