#include "ConfigCgi.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigCgi::ConfigCgi(void) :
	fileExtension_(".php"),
	rootPath_(),
	scriptPath_(),
	workingDirectory_()
{}

ConfigCgi::ConfigCgi(const ConfigCgi& other) :
	fileExtension_(other.fileExtension_),
	rootPath_(other.rootPath_),
	scriptPath_(other.scriptPath_),
	workingDirectory_(other.workingDirectory_)
{}

ConfigCgi::~ConfigCgi()
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigCgi&	ConfigCgi::operator=(const ConfigCgi& rhs)
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

void	ConfigCgi::setFileExtension(const std::string& fileExtension)
{
	fileExtension_ = fileExtension;
}

void	ConfigCgi::setRootPath(const Path& rootPath)
{
	rootPath_ = rootPath;
}

void	ConfigCgi::setScriptPath(const Path& scriptPath)
{
	scriptPath_ = scriptPath;
}

void	ConfigCgi::setWorkingDirectory(const Path& workingDirectory)
{
	workingDirectory_ = workingDirectory;
}

void	ConfigCgi::addAllowedMethod(HttpMethodType allowedMethod)
{
	allowedMethods_.push_back(allowedMethod);
}

// --- Getters ---

const std::string&	ConfigCgi::getFileExtension(void) const
{
	return (fileExtension_);
}

const Path&	ConfigCgi::getRootPath(void) const
{
	return (rootPath_);
}

const Path&	ConfigCgi::getScriptPath(void) const
{
	return (scriptPath_);
}

const Path&	ConfigCgi::getWorkingDirectory(void) const
{
	return (workingDirectory_);
}

const std::vector<HttpMethodType>&	ConfigCgi::getAllowedMethods(void) const
{
	return (allowedMethods_);
}
