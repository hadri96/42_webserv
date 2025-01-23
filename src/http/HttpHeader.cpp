#include "HttpHeader.hpp"
#include "HttpConnectionType.hpp"
#include "ToString.hpp"

#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

// Using example values for testing purposes: 
HttpHeader::HttpHeader(void) :
    host_("www.example.com"),
    userAgent_("agent"),
    contentLength_(0),
    contentType_("text/plain"),
    connectionType_(CLOSED),
    accept_("text/html"),
    acceptEncoding_("gzip"),
    acceptLanguage_("en-US,en,q=0.9")
{}

HttpHeader::HttpHeader(const HttpHeader& other) :
    host_(other.host_),
    userAgent_(other.userAgent_),
    contentLength_(other.contentLength_),
    contentType_(other.contentType_),
    connectionType_(other.connectionType_),
    accept_(other.accept_),
    acceptEncoding_(other.acceptEncoding_),
    acceptLanguage_(other.acceptLanguage_)
{}

HttpHeader::~HttpHeader(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpHeader&	HttpHeader::operator=(const HttpHeader& other)
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
const std::string& HttpHeader::getHost() const 
{
    return (host_);
}

// Getter for userAgent_
const std::string& HttpHeader::getUserAgent() const 
{
    return (userAgent_);
}

// Getter for contentLength_
std::size_t HttpHeader::getContentLength() const 
{
    return (contentLength_);
}

// Getter for contentType_
const std::string& HttpHeader::getContentType() const 
{
    return (contentType_);
}

// Getter for connectionType_
HttpConnectionType HttpHeader::getConnectionType() const 
{
    return (connectionType_);
}

std::string HttpHeader::getConnectionTypeString() const
{
    if (connectionType_ == 0)
        return ("CLOSED");
    else if (connectionType_ == 1)
        return ("KEEP_ALIVE");
    else 
        return ("UNDEFINED");
}

// Getter for accept_
const std::string& HttpHeader::getAccept() const 
{
    return (accept_);
}

// Getter for acceptEncoding_
const std::string& HttpHeader::getAcceptEncoding() const 
{
    return (acceptEncoding_);
}

// Getter for acceptLanguage_
const std::string& HttpHeader::getAcceptLanguage() const 
{
    return (acceptLanguage_);
}

// =============================================================================
// Setters
// =============================================================================

// Setter for host_
void HttpHeader::setHost(const std::string& host) 
{
    host_ = host;
}

// Setter for userAgent_
void HttpHeader::setUserAgent(const std::string& userAgent) 
{
    userAgent_ = userAgent;
}

// Setter for contentLength_
void HttpHeader::setContentLength(std::size_t contentLength) 
{
    contentLength_ = contentLength;
}

// Setter for contentType_
void HttpHeader::setContentType(const std::string& contentType) 
{
    contentType_ = contentType;
}

// Setter for connectionType_
void HttpHeader::setConnectionType(HttpConnectionType connectionType) 
{
    connectionType_ = connectionType;
}

// Setter for accept_
void HttpHeader::setAccept(const std::string& accept) 
{
    accept_ = accept;
}

// Setter for acceptEncoding_
void HttpHeader::setAcceptEncoding(const std::string& acceptEncoding) 
{
    acceptEncoding_ = acceptEncoding;
}

// Setter for acceptLanguage_
void HttpHeader::setAcceptLanguage(const std::string& acceptLanguage) 
{
    acceptLanguage_ = acceptLanguage;
}

// =============================================================================
// Private Methods
// =============================================================================

std::string     HttpHeader::generateHttpHeaderString() const
{
    std::ostringstream  HttpHeaders;

    HttpHeaders << "Host: " << getHost() << "\r\n";
    HttpHeaders << "User Agent: " << getUserAgent() << "\r\n";
    HttpHeaders << "Content Length: " << toString(getContentLength()) << "\r\n";
    HttpHeaders << "Connection Type: " << getConnectionTypeString() << "\r\n";
    HttpHeaders << "Accept: " << getAccept() << "\r\n";
    HttpHeaders << "Accept Encoding: " << getAcceptEncoding() << "\r\n";
    HttpHeaders << "Accept Language: " << getAcceptLanguage() << "\r\n";
    
    return (HttpHeaders.str());
}
