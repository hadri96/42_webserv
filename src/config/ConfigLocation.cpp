#include "ConfigLocation.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigLocation::ConfigLocation(void) :
	uri_(),
	rootPath_(),
	allowedMethods_(),
	redirection_(),
	autoIndex_(false),
	defaultFile_(),
	uploadDirectory_(),
	clientMaxBodySize_(-1),
	isCgi_(false),
	cgi_()
{}

ConfigLocation::ConfigLocation(const ConfigLocation& other) :
	uri_(other.uri_),
	rootPath_(other.rootPath_),
	allowedMethods_(other.allowedMethods_),
	redirection_(other.redirection_),
	autoIndex_(other.autoIndex_),
	defaultFile_(other.defaultFile_),
	uploadDirectory_(other.uploadDirectory_),
	isCgi_(other.isCgi_),
	cgi_(other.cgi_)
{}
ConfigLocation::~ConfigLocation(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigLocation&	ConfigLocation::operator=(const ConfigLocation& rhs)
{
	if (this == &rhs)
		return (*this);
	
	uri_ = rhs.uri_;
	rootPath_ = rhs.rootPath_;
	allowedMethods_ = rhs.allowedMethods_;
	redirection_ = rhs.redirection_;
	autoIndex_ = rhs.autoIndex_;
	defaultFile_ = rhs.defaultFile_;
	uploadDirectory_ = rhs.uploadDirectory_;
	isCgi_ = rhs.isCgi_;
	cgi_ = rhs.cgi_;

	return (*this);
}

bool	ConfigLocation::operator==(const Uri& uri) const
{
	return (uri_ == uri);
}

/*std::ostream&	operator<<(std::ostream& os, Location& object)
{
	os << "--- Location ---" << std::endl;
	os << "  uri : " << object.getUri().getUri() << std::endl;
	os << "  root path : " << object.getRootPath().getPath() << std::endl;
	os << "  autoindex : " << object.getAutoIndex() << std::endl;
	
	// limit except ?
	return (os);
}*/

/*
std::ostream& operator<<(std::ostream& os, Location& object) {
    std::ostringstream oss;

    oss << "--- Location ---" << std::endl;
    oss << "  uri : " << object.getUri().getUri() << std::endl;
    oss << "  root path : " << object.getRootPath().getPath() << std::endl;
    oss << "  autoindex : " << object.getAutoIndex() << std::endl;

    Logger::logger()->log(LOG_DEBUG, oss.str()); // Log the message with the prefix
    
    // No longer output to 'os' here; remove os << oss.str();

    return os;
}
*/

void	ConfigLocation::log(void)
{
    std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Location", 2);

    oss << "  uri : " << getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

    oss << "  root path : " << getRootPath();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  allowed methods : ";

	for (size_t i = 0; i != allowedMethods_.size(); ++i)
		oss << httpMethodToString(allowedMethods_[i]) << " ";
	Logger::logger()->log(LOG_DEBUG, oss);

    oss << "  autoindex : " << getAutoIndex();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  index : " << getDefaultFile();
	Logger::logger()->log(LOG_DEBUG, oss);

	if (getConfigRedirection().getStatusCode() != 0)
	{
		oss << "  redirection : ";
		Logger::logger()->log(LOG_DEBUG, oss);

		oss << "    status code : " << getConfigRedirection().getStatusCode();
		Logger::logger()->log(LOG_DEBUG, oss);

		oss << "    uri : " << getConfigRedirection().getUri();
		Logger::logger()->log(LOG_DEBUG, oss);
	}

}

// =============================================================================
// Setters and Getters
// =============================================================================

// --- Setters ---

void	ConfigLocation::setUri(Uri uri)
{
	uri_ = uri;
}

void	ConfigLocation::setRootPath(Path rootPath)
{
	rootPath_ = rootPath;
}

void	ConfigLocation::setAutoIndex(bool autoIndex)
{
	autoIndex_ = autoIndex;
}

void	ConfigLocation::setConfigRedirection(ConfigRedirection redirection)
{
	redirection_ = redirection;
}

void	ConfigLocation::setDefaultFile(const Path& defaultFile)
{
	defaultFile_ = defaultFile;
}

void	ConfigLocation::setUploadDirectory(const Path& uploadDirectory)
{
	uploadDirectory_ = uploadDirectory;
}

void	ConfigLocation::setIsCgi(bool isCgi)
{
	isCgi_ = isCgi;
}

void	ConfigLocation::setCgi(const ConfigCgi& cgi)
{
	cgi_ = cgi;
}

void	ConfigLocation::addAllowedMethod(HttpMethodType method)
{
	allowedMethods_.push_back(method);
}

// --- Getters ---

const Uri&	ConfigLocation::getUri(void) const
{
	return (uri_);
}

const Path& 	ConfigLocation::getRootPath(void) const
{
	return (rootPath_);
}

const std::string 	ConfigLocation::getRootPathString(void) const
{
	return (rootPath_);
}

const ConfigRedirection&	ConfigLocation::getConfigRedirection(void) const
{
	return (redirection_);
}

bool	ConfigLocation::getAutoIndex(void) const
{
	return (autoIndex_);
}

const Path&	ConfigLocation::getDefaultFile(void) const
{
	return (defaultFile_);
}

const Path&	ConfigLocation::getUploadDirectory(void) const
{
	return (uploadDirectory_);
}

bool	ConfigLocation::getIsCgi(void) const
{
	return (isCgi_);
}

const ConfigCgi&	ConfigLocation::getCgi(void) const
{
	return (cgi_);
}

const std::vector<HttpMethodType>&	ConfigLocation::getAllowedMethods(void) const
{
	return (allowedMethods_);
}

int	ConfigLocation::getClientMaxBodySize(void) const
{
	return (clientMaxBodySize_);
}

// =============================================================================
// Public Methods
// =============================================================================

bool	ConfigLocation::isMethodAllowed(HttpMethodType method) const
{

	for (size_t i = 0; i != allowedMethods_.size(); ++i)
	{
		if (allowedMethods_[i] == method)
			return (true);
	}
	return (false);
}

bool	ConfigLocation::isSizeAllowed(int byteSize) const
{
	

	if (byteSize <= clientMaxBodySize_)
		return (true);
	return (false);
}
