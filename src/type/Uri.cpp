#include "Uri.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Uri::Uri(void) :
	PathOrUri()
{}

Uri::Uri(const Uri& other) :
	PathOrUri(other)
{}

Uri::Uri(const std::string& str) :
	PathOrUri(str)
{}

Uri::~Uri()
{}

// =============================================================================
// Operators Overload
// =============================================================================

Uri&	Uri::operator=(const Uri& rhs)
{
	if (this == &rhs)
		return (*this);

	PathOrUri::operator=(rhs);
	return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

Uri	Uri::getParent(void) const
{
	PathOrUri parent = PathOrUri::getParent();
	return Uri(parent);
}