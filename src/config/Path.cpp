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

Path	operator+(const Path& path, const Uri& uri)
{
    return (path.addUri(uri));
}

// =============================================================================
// Getters
// =============================================================================

std::string	Path::getPath() const
{
	return (path_);
}

std::string	Path::getPath(Config& config) const
{
	(void)config;

	if (isInFileSystem())
	{
		Logger::logger()->log(LOG_INFO, "Path is valid.");
		return (path_);
	}
	else
	{
		Logger::logger()->log(LOG_ERROR, "Not a valid Path");
		return ("");
	}
}

// =============================================================================
// Public Methods
// =============================================================================

const Path	Path::addUri(const Uri& uri) const
{
    return (Path(path_ + uri.getUri()));
}

bool	Path::isInFileSystem() const
{
	// Check if path is actually in the file system
	return (false);
}


