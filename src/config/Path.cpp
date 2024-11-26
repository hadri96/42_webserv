#include "Path.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Path::Path(void) :
	path_("")
{}

Path::Path(const Path& other) :
	path_(other.path_)
{}

Path::~Path(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Path&	Path::operator=(const Path& rhs)
{
	if (this == &rhs)
		return (*this);
	path_ = rhs.path_;

	return (*this);
}