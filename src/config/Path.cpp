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

std::string	Path::getPath(Config& config) const
{
	if (isInFileSystem())
	{
		if (isInConfig(config))
		{
			Logger::logger()->log(LOG_INFO, "Path is valid.");
			return (path_);
		}
		else
		{
			Logger::logger()->log(LOG_ERROR, "Requested path " + path_ + " is not valid in Config.");
			return ("");
		}
	}
	else
	{
		Logger::logger()->log(LOG_ERROR, "Not a valid Path");
		return ("");
	}
}

// =============================================================================
// Private Methods
// =============================================================================

bool	Path::isInFileSystem() const
{
	// Check if path is actually in the file system
	return (true);
}

// Cette fonction devrait etre faite par le config : Config->isAvailablePath(Path& path)
bool	Path::isInConfig(Config& config) const
{
	// Check if path corresponds to the path given in the config file
	// config file path can be found here: request.getRequestLine().getRequestTarget().getPath(config)
	(void)config;
	return (true);
}
