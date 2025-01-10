#include "HttpRedirection.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRedirection::HttpRedirection(void) :
	statusCode_(0),
	uri_()
{}

HttpRedirection::HttpRedirection(const HttpRedirection& other) :
	statusCode_(other.statusCode_),
	uri_(other.uri_)
{}

HttpRedirection::HttpRedirection(int statusCode, Uri uri) :
	statusCode_(statusCode),
	uri_(uri)
{}

HttpRedirection::~HttpRedirection(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpRedirection&	HttpRedirection::operator=(const HttpRedirection& rhs)
{
	if (this == &rhs)
		return (*this);

	statusCode_ = rhs.statusCode_;
	uri_ = rhs.uri_;

	return (*this);
}

std::ostream&	operator<<(std::ostream& os, HttpRedirection& object)
{
	os << "--- Redirection ---" << std::endl;
	os << "  status code : " << object.getStatusCode() << std::endl;
	os << "  uri : " << object.getUri().getUri() << std::endl;

	return (os);
}

// =============================================================================
// Setters and Getters
// =============================================================================

int	HttpRedirection::getStatusCode(void) const
{
	return (statusCode_);
}

const Uri&	HttpRedirection::getUri(void) const
{
	return (uri_);
}