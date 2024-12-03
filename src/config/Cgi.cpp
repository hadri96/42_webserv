#include "Cgi.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Cgi::Cgi(void) :
	fileExtension_(".php"),
	rootPath_(),
	scriptPath_(),
	workingDirectory_()
{}

Cgi::Cgi(const Cgi& other) :
	fileExtension_(other.fileExtension_),
	rootPath_(other.rootPath_),
	scriptPath_(other.scriptPath_),
	workingDirectory_(other.workingDirectory_)
{}

Cgi::~Cgi()
{}

// =============================================================================
// Operators Overload
// =============================================================================

Cgi&	Cgi::operator=(const Cgi& rhs)
{
	if (this == &rhs)
		return (*this);

	fileExtension_ = rhs.fileExtension_;
	rootPath_ = rhs.rootPath_;
	scriptPath_ = rhs.scriptPath_;
	workingDirectory_ = rhs.workingDirectory_;

	return (*this);
}

// =============================================================================
// Setters and Getters
// =============================================================================

// --- Setters ---

void	Cgi::setFileExtension(const std::string& fileExtension)
{
	fileExtension_ = fileExtension;
}

void	Cgi::setRootPath(const Path& rootPath)
{
	rootPath_ = rootPath;
}

void	Cgi::setScriptPath(const Path& scriptPath)
{
	scriptPath_ = scriptPath;
}

void	Cgi::setWorkingDirectory(const Path& workingDirectory)
{
	workingDirectory_ = workingDirectory;
}

void	Cgi::addAllowedMethod(HttpMethodType allowedMethod)
{
	allowedMethods_.push_back(allowedMethod);
}

// --- Getters ---

const std::string&	Cgi::getFileExtension(void) const
{
	return (fileExtension_);
}

const Path&	Cgi::getRootPath(void) const
{
	return (rootPath_);
}

const Path&	Cgi::getScriptPath(void) const
{
	return (scriptPath_);
}

const Path&	Cgi::getWorkingDirectory(void) const
{
	return (workingDirectory_);
}

const std::vector<HttpMethodType>&	Cgi::getAllowedMethods(void) const
{
	return (allowedMethods_);
}
