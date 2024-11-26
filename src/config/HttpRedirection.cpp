#include "HttpRedirection.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRedirection::HttpRedirection(void) :
	statusCode_(0),
	path_()
{}

HttpRedirection::HttpRedirection(const HttpRedirection& other) :
	statusCode_(other.statusCode_),
	path_(other.path_)
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
	path_ = rhs.path_;

	return (*this);
}
