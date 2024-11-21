#include "../../includes/webserv.hpp"

// =============================================================================
// Public Methods
// =============================================================================

// ·············································································
// Constructors and Destructor
// ·············································································

Client::Client(int fd) : client_socket(fd), is_reading(true), is_writing(false) {}

Client::~Client() {}

// ·············································································
// Public Methods
// ·············································································

void        Client::assignRequest(HttpRequest *request_ptr)
{
    current_request = *request_ptr;
}

void        Client::assignResponse(HttpResponse *response_ptr)
{
    current_response = *response_ptr;
}

// ·············································································
// Getters and Utils
// ·············································································


HttpRequest&         Client::getCurrentRequest()
{
    return (this->current_request);
}

HttpResponse&        Client::getCurrentResponse()
{
    return (this->current_response);
}

int         Client::getClientSocket()
{
    return (client_socket);
}

std::string Client::getWriteBuffer()
{
    return (write_buffer);
}

// =============================================================================
// Private Methods
// =============================================================================

