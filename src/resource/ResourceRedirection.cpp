#include "ResourceRedirection.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ResourceRedirection::ResourceRedirection(void)
{}

ResourceRedirection::ResourceRedirection(const ResourceRedirection& other) :
    Resource(other.code_),
	uri_(other.uri_)
{}

ResourceRedirection::ResourceRedirection(int code, Uri uri) :
    Resource(code),
	uri_(uri)
{}

ResourceRedirection::~ResourceRedirection(void)
{}

// =============================================================================
// Public Methods
// =============================================================================

Uri	ResourceRedirection::getUri(void) const
{
	return (uri_);
}

// =============================================================================
// Operators Overload
// =============================================================================

ResourceRedirection&	ResourceRedirection::operator=(const ResourceRedirection& rhs)
{
    (void) rhs;
    return (*this);
}
