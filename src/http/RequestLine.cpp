#include "RequestLine.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

RequestLine::RequestLine(void) : 
	method_(GET),
	requestTarget_("www/html/example_response.html"),
	httpVersion_("HTTP/1.1")
{}

RequestLine::RequestLine(const RequestLine& other) :
	method_(other.method_),
    requestTarget_(other.requestTarget_),
    httpVersion_(other.httpVersion_)
{}

RequestLine::~RequestLine(void) {}

// =============================================================================
// Operators Overload
// =============================================================================

RequestLine&	RequestLine::operator=(const RequestLine& other)
{
	if (this == &other)
		return (*this);
	method_ = other.method_;
    requestTarget_ = other.requestTarget_;
    httpVersion_ = other.httpVersion_;

	return (*this);
}

// =============================================================================
// Getters
// =============================================================================

// Getter for method_
HttpMethodType RequestLine::getMethod() const 
{
    return (method_);
}

// Getter for requestTarget_
const Path& RequestLine::getRequestTarget() const 
{
    return (requestTarget_);
}

// Getter for httpVersion_
const std::string& RequestLine::getHttpVersion() const 
{
    return (httpVersion_);
}

// Getter for queryString_
const std::string& RequestLine::getQueryString() const 
{
    return (queryString_);
}
