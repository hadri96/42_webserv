#include "RequestLine.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

RequestLine::RequestLine(void) : 
	method_(GET),
	relativeUri_("www/html/example_response.html"),
	httpVersion_("HTTP/1.1")
{}

RequestLine::RequestLine(const RequestLine& other) :
	method_(other.method_),
    relativeUri_(other.relativeUri_),
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
    relativeUri_ = other.relativeUri_;
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

// String getter for method_
std::string RequestLine::getMethodString() const 
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
const Uri& RequestLine::getRelativeUri() const 
{
    return (relativeUri_);
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
