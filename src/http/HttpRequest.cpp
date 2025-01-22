#include "HttpRequest.hpp"
#include "ToString.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequest::HttpRequest() : 
    rawRequest_(""),
    requestLine_(HttpRequestLine()),
    header_(HttpHeader()),
    body_("")
    {}

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
const HttpRequestLine& HttpRequest::getRequestLine() const 
{
    return (requestLine_);
}

// Getter for header_
const HttpHeader& HttpRequest::getHttpHeader() const 
{
    return (header_);
}

// Getter for body_
const std::string& HttpRequest::getBody() const 
{
    return (body_);
}

int HttpRequest::getBodySize() const 
{
    return (body_.length() * sizeof(char));
}

const Uri& HttpRequest::getUri() const
{
    return (requestLine_.getRelativeUri());
}


// ··· "Deep" Getters and utils ···

const std::string   HttpRequest::getRelativeUri() const
{
    Logger::logger()->log(LOG_DEBUG, "getting URI");
    return (requestLine_.getRelativeUri());
}

HttpMethodType    HttpRequest::getMethod() const
{
    return (requestLine_.getMethod());
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
	          << requestLine_.getRelativeUri() << " ; "
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