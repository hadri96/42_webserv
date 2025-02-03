#include "HttpRequestLine.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequestLine::HttpRequestLine(void) : 
	method_(GET),
	uri_("/"),
	httpVersion_("HTTP/1.1")
{}

HttpRequestLine::HttpRequestLine(const HttpRequestLine& other) :
	method_(other.method_),
    uri_(other.uri_),
    httpVersion_(other.httpVersion_),
    queryString_(other.queryString_)
{}

HttpRequestLine::~HttpRequestLine(void)
{}

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

// --- Http Method ---
HttpMethodType HttpRequestLine::getMethod() const 
{
    return (method_);
}

void    HttpRequestLine::setMethod(HttpMethodType httpMethod)
{
    method_ = httpMethod;
}

// --- URI ---
const Uri& HttpRequestLine::getUri() const 
{
    return (uri_);
}

void	HttpRequestLine::setUri(Uri uri)
{
	uri_ = uri;
}

// --- HTTP Version ---
const std::string& HttpRequestLine::getHttpVersion() const 
{
    return (httpVersion_);
}

void    HttpRequestLine::setHttpVersion(const std::string httpVersion)
{
    httpVersion_ = httpVersion;
}

// --- Query string ---
const std::string& HttpRequestLine::getQueryString() const 
{
    return (queryString_);
}

void    HttpRequestLine::setQueryString(const std::string queryString)
{
    queryString_ = queryString;
}