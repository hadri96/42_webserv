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

HttpRedirection::HttpRedirection(int statusCode, const Path& path) :
	statusCode_(statusCode),
	path_(path)
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

// =============================================================================
// Setters and Getters
// =============================================================================

int	HttpRedirection::getStatusCode(void) const
{
	return (statusCode_);
}

const Path&	HttpRedirection::getPath(void) const
{
	return (path_);
}