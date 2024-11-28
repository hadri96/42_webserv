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

Path::Path(const std::string path) :
	path_(path)
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

// =============================================================================
// Getters
// =============================================================================

std::string	Path::getPath() const
{
	return (path_);
}