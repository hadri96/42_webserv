#include "Path.hpp"

#include <unistd.h>
#include <stdexcept>
#include <sys/stat.h>
#include <fstream>

#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Path::Path(void) :
	PathOrUri()
{}

Path::Path(const Path& other) :
	PathOrUri(other)
{}

Path::Path(const PathOrUri& other) :
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

std::string	Path::getExtension(void) const
{
	std::string filename;
	std::vector<std::string> components = PathOrUri::getComponents();

	if (components.empty())
		return ("");

	filename = components.back();
	size_t dotPos = filename.find_last_of('.');

	if (dotPos == std::string::npos)
        return ("");

	return filename.substr(dotPos + 1);
}

std::string	Path::read(void) const
{
	std::string         line;
    std::string         content;

	std::string			path = *this;
    std::ifstream       fileStream(path.c_str());

    /*if (fileStream.is_open())
        Logger::logger()->log(LOG_INFO, "File opened: " + path);*/
    while (std::getline(fileStream, line))
        content.append(line, 0, line.length()).append("\n");
    fileStream.close();
	return (content);
}

Path Path::fromPathOrUri(const PathOrUri& pathOrUri)
{
    return Path(pathOrUri);
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
