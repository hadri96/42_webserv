#include "Header.hpp"
#include "ConnectionType.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

// Using example values for testing purposes: 
Header::Header(void) :
    host_("www.example.com"),
    userAgent_("agent"),
    contentLength_(0),
    contentType_("text/plain"),
    connectionType_(CLOSED),
    accept_("text/html"),
    acceptEncoding_("gzip"),
    acceptLanguage_("en-US,en,q=0.9")
{}

Header::Header(const Header& other) :
    host_(other.host_),
    userAgent_(other.userAgent_),
    contentLength_(other.contentLength_),
    contentType_(other.contentType_),
    connectionType_(other.connectionType_),
    accept_(other.accept_),
    acceptEncoding_(other.acceptEncoding_),
    acceptLanguage_(other.acceptLanguage_)
{}

Header::~Header(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Header&	Header::operator=(const Header& other)
{
	if (this == &other)
		return (*this);
    // variables = other.variables
	return (*this);
}

// =============================================================================
// Getters
// =============================================================================


// Getter for host_
const std::string& Header::getHost() const 
{
    return (host_);
}

// Getter for userAgent_
const std::string& Header::getUserAgent() const 
{
    return (userAgent_);
}

// Getter for contentLength_
std::size_t Header::getContentLength() const 
{
    return (contentLength_);
}

// Getter for contentType_
const std::string& Header::getContentType() const 
{
    return (contentType_);
}

// Getter for connectionType_
ConnectionType Header::getConnectionType() const 
{
    return (connectionType_);
}

std::string Header::getConnectionTypeString() const
{
    if (connectionType_ == 0)
        return ("CLOSED");
    else if (connectionType_ == 1)
        return ("KEEP_ALIVE");
    else 
        return ("UNDEFINED");
}


// Getter for accept_
const std::string& Header::getAccept() const 
{
    return (accept_);
}

// Getter for acceptEncoding_
const std::string& Header::getAcceptEncoding() const 
{
    return (acceptEncoding_);
}

// Getter for acceptLanguage_
const std::string& Header::getAcceptLanguage() const 
{
    return (acceptLanguage_);
}
