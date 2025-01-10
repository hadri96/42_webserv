#include "Path.hpp"
#include <unistd.h>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Path::Path(void) :
	path_(""),
	absPath_(getWorkingDirectory() + "/" + path_)
{}

Path::Path(const Path& other) :
	path_(other.path_),
	absPath_(getWorkingDirectory() + "/" + path_)
{}

Path::Path(const std::string path) :
	path_(path),
	absPath_(getWorkingDirectory() + "/" + path_)
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

std::string	Path::getAbsPath() const
{
	return (absPath_);
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
	if (access((absPath_).c_str(), F_OK) == 0)
	{
		Logger::logger()->log(LOG_DEBUG, absPath_ + " can be accessed");
		return (true);
	}
	Logger::logger()->log(LOG_DEBUG, absPath_ + " cannot be accessed");
	return (false);
}

std::string Path::getWorkingDirectory()
{
    char 	cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        throw (std::runtime_error("Failed to get current working directory"));
    return (std::string(cwd));
}
