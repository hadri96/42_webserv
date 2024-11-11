#include "../../includes/webserv.hpp"

// =============================================================================
// Public Methods
// =============================================================================

// ·············································································
// Constructors and Destructor
// ·············································································

ClientConnection::ClientConnection(int fd) : client_socket(fd), is_reading(true), is_writing(false) {}

ClientConnection::~ClientConnection() {}

// ·············································································
// Public Methods
// ·············································································

void        ClientConnection::assignRequest(HTTPRequest *request_ptr)
{
    current_request = *request_ptr;
}

void        ClientConnection::assignResponse(HTTPResponse *response_ptr)
{
    current_response = *response_ptr;
}

// ·············································································
// Getters and Utils
// ·············································································


HTTPRequest&         ClientConnection::getCurrentRequest()
{
    return (this->current_request);
}

HTTPResponse&        ClientConnection::getCurrentResponse()
{
    return (this->current_response);
}

int         ClientConnection::getClientSocket()
{
    return (client_socket);
}

std::string ClientConnection::getWriteBuffer()
{
    return (write_buffer);
}

// =============================================================================
// Private Methods
// =============================================================================

