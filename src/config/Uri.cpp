#include "Uri.hpp"
#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Uri::Uri(void) :
	uri_()
{}

Uri::Uri(const Uri& other) :
	uri_(other.uri_)
{}

Uri::Uri(const std::string& uri) :
	uri_(uri)
{}

Uri::~Uri(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Uri&	Uri::operator=(const Uri& rhs)
{
	if (this == &rhs)
		return (*this);
	
	uri_ = rhs.uri_;
	return (*this);
}

// =============================================================================
// Getters and Setters
// =============================================================================

const std::string&	Uri::getUri(void) const
{
	return (uri_);
}
