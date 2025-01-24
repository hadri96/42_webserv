#include "HttpRequestLine.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequestLine::HttpRequestLine(void) : 
	method_(GET),
	uri_("/example_response.html"),
	httpVersion_("HTTP/1.1")
{}

HttpRequestLine::HttpRequestLine(const HttpRequestLine& other) :
	method_(other.method_),
    uri_(other.uri_),
    httpVersion_(other.httpVersion_)
{}

HttpRequestLine::~HttpRequestLine(void) {}

// =============================================================================
// Operators Overload
// =============================================================================

HttpRequestLine&	HttpRequestLine::operator=(const HttpRequestLine& other)
{
	if (this == &other)
		return (*this);
	method_ = other.method_;
    uri_ = other.uri_;
    httpVersion_ = other.httpVersion_;

	return (*this);
}

// =============================================================================
// Getters
// =============================================================================

// Getter for method_
HttpMethodType HttpRequestLine::getMethod() const 
{
    return (method_);
}

// String getter for method_
std::string HttpRequestLine::getMethodString() const 
{
    if (method_ == 0)
        return ("GET");
    else if (method_ == 1)
        return ("POST");
    else if (method_ == 2)
        return ("DELETE");
    else
        return ("UNDEFINED");
}

// Getter for relativeUri_
const Uri& HttpRequestLine::getUri() const 
{
    return (uri_);
}

void	HttpRequestLine::setUri(Uri uri)
{
	uri_ = uri;
}

// Getter for httpVersion_
const std::string& HttpRequestLine::getHttpVersion() const 
{
    return (httpVersion_);
}

// Getter for queryString_
const std::string& HttpRequestLine::getQueryString() const 
{
    return (queryString_);
}
