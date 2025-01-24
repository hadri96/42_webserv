#include "HttpRequest.hpp"
#include "ToString.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequest::HttpRequest() : 
    rawRequest_(),
    //"GET /cgi-bin/hello.php?name=newFileMickey&content=donaldDucknotdonaldTrump HTTP/1.1\r\n Host: http://127.0.0.1:7777/\r\n Connection: close\r\n\r\n"),
    requestLine_(HttpRequestLine()),
    header_(HttpHeader()),
    body_("")
{
    inputs_.insert(std::make_pair("name", "newFileMickey"));
    inputs_.insert(std::make_pair("content", "donaldDuck not donaldTrump"));
}

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
    return (requestLine_.getUri());
}

std::string HttpRequest::getInput(std::string key)
{
    return (inputs_[key]);
}

// ··· "Deep" Getters and utils ···

HttpMethodType    HttpRequest::getMethod() const
{
    return (requestLine_.getMethod());
}

HttpMimeType    HttpRequest::getMimeType() const
{
    return (header_.getMimeType());
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
	          << requestLine_.getUri() << " ; "
	          << requestLine_.getHttpVersion() << std::endl;

    ss << "\nDummy Header:\n\n"
	          << "host_: " << header_.getHost() << "\n"
	          << "userAgent_: " << header_.getUserAgent() << "\n"
	          << "contentLength_: " << toString(header_.getContentLength()) << "\n"
	          << "contentType_: " << header_.getMimeType() << "\n"
	          << "connectionType_: " << header_.getConnectionTypeString() << "\n"
	          << "accept_: " << header_.getAccept() << "\n"
	          << "acceptEncoding_: " << header_.getAcceptEncoding() << "\n"
	          << "acceptLanguage_: " << header_.getAcceptLanguage() << std::endl;

    return (ss.str());
}