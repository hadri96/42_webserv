#include "Path.hpp"

#include <unistd.h>
#include <stdexcept>
#include <sys/stat.h>

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

// =============================================================================
// Public Methods
// =============================================================================

Path	Path::getParent(void) const
{
	PathOrUri parent = PathOrUri::getParent();
	return Path(parent);
}

Path	Path::getAbsPath(void) const
{
	return static_cast<Path>(getWorkingDirectory() / *this);
}

bool	Path::isInFileSystem(void) const
{
	std::string path = *this;
	if (access(path.c_str(), F_OK) == 0)
		return (true);
	return (false);
}

bool	Path::isDir(void) const
{
    struct stat path_stat;
	std::string path = *this;
    if (stat(path.c_str(), &path_stat) != 0)
        return (false);
    return S_ISDIR(path_stat.st_mode);
}

// =============================================================================
// Private Methods
// =============================================================================

Path	Path::getWorkingDirectory(void) const
{
    char 	cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        throw (std::runtime_error("Failed to get current working directory"));

    return (Path(std::string(cwd)));
}
