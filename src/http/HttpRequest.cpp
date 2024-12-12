#include "HttpRequest.hpp"
#include "ToString.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequest::HttpRequest() : 
    rawRequest_(""),
    requestLine_(RequestLine()),
    header_(Header()),
    body_(""){}

HttpRequest::~HttpRequest() {}

void    HttpRequest::appendRequest(std::string input)
{
    if (rawRequest_.empty())
        rawRequest_ = input;
    else 
        rawRequest_.append(input, 0, input.length());
}

// =============================================================================
// Getters
// =============================================================================


// Getter for rawRequest_
const std::string& HttpRequest::getRawRequest() const 
{
    return (rawRequest_);
}

// Getter for requestLine_
const RequestLine& HttpRequest::getRequestLine() const 
{
    return (requestLine_);
}

const std::string   HttpRequest::getRequestTarget() const
{
    return (getRequestLine().getRequestTarget().getPath());
}

// Getter for header_
const Header& HttpRequest::getHeader() const 
{
    return (header_);
}

// Getter for body_
const std::string& HttpRequest::getBody() const 
{
    return (body_);
}

// =============================================================================
// Public Methods 
// =============================================================================


std::string   HttpRequest::generatePrintString()
{
    std::stringstream ss;

    ss << "Client Request (RawRequest): " << rawRequest_ << std::endl;
	
    ss << "Dummy RequestLine: \n\n" 
	          << requestLine_.getMethodString() << " ; "
	          << requestLine_.getRequestTarget().getPath() << " ; "
	          << requestLine_.getHttpVersion() << std::endl;

    ss << "\nDummy Header:\n\n"
	          << "host_: " << header_.getHost() << "\n"
	          << "userAgent_: " << header_.getUserAgent() << "\n"
	          << "contentLength_: " << toString(header_.getContentLength()) << "\n"
	          << "contentType_: " << header_.getContentType() << "\n"
	          << "connectionType_: " << header_.getConnectionTypeString() << "\n"
	          << "accept_: " << header_.getAccept() << "\n"
	          << "acceptEncoding_: " << header_.getAcceptEncoding() << "\n"
	          << "acceptLanguage_: " << header_.getAcceptLanguage() << std::endl;

    return (ss.str());
}