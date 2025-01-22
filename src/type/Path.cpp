#include "Path.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Path::Path(void) :
	PathOrUri()
{}

Path::Path(const Path& other) :
	PathOrUri(other)
{}

Path::Path(const std::string& str) :
	PathOrUri(str)
{}

Path::~Path()
{}

// =============================================================================
// Operators Overload
// =============================================================================

Path&	Path::operator=(const Path& rhs)
{
	if (this == &rhs)
		return (*this);

	PathOrUri::operator=(rhs);
	return (*this);
}
