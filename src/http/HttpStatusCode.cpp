#include "HttpStatusCode.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpStatusCode::HttpStatusCode(void)
{
    addStatusCode(301, "Moved Permanently", "The requested resource has been permanently moved to a new location.");
    addStatusCode(302, "Moved Temporarily", "The requested resource is temporarily located at a different URL.");
    addStatusCode(403, "Forbidden", "You do not have permission to access this resource.");
    addStatusCode(404, "Not Found", "The page or resource you requested could not be found on this server.");
    addStatusCode(405, "Method Not Allowed", "The method specified in the request is not allowed for the resource.");
    addStatusCode(413, "Payload Too Large", "The request entity is larger than limits defined by the server.");
}

HttpStatusCode::HttpStatusCode(const HttpStatusCode& other)
{
    (void) other;
}

HttpStatusCode::~HttpStatusCode(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpStatusCode&   HttpStatusCode::operator=(const HttpStatusCode& rhs)
{
    (void) rhs;
    return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

std::string  HttpStatusCode::getStatusLine(int code)
{
    for (size_t i = 0; i != code_.size(); ++i)
    {
        if (code_[i] == code)
            return (statusLine_[i]);
    }

    return ("");
}

std::string  HttpStatusCode::getMessage(int code)
{
    for (size_t i = 0; i != code_.size(); ++i)
    {
        if (code_[i] == code)
            return (message_[i]);
    }
    return ("");
}


// =============================================================================
// Private Methods
// =============================================================================

void    HttpStatusCode::addStatusCode(int code, std::string statusLine, std::string message)
{
    code_.push_back(code);
    statusLine_.push_back(statusLine);
    message_.push_back(message);
}