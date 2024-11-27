#include "RequestLine.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

RequestLine::RequestLine(void) :
{}

RequestLine::RequestLine(const RequestLine& other) :
	method_(other.method_),
    requestTarget_(other.requestTarget_),
    httpVersion_(other.httpVersion_)
{}

RequestLine::~RequestLine(void)
{}

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
