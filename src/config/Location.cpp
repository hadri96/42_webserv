#include "Location.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Location::Location(void) :
	uri_(),
	rootPath_(),
	allowedMethods_(),
	redirection_(),
	autoIndex_(false),
	defaultFile_(),
	uploadDirectory_(),
	isCgi_(false),
	cgi_()
{}

Location::Location(const Location& other) :
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
Location::~Location(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Location&	Location::operator=(const Location& rhs)
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

bool	Location::operator==(const Uri& uri) const
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

void	Location::log(void)
{
    std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Location", 2);

    oss << "  uri : " << getUri().getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

    oss << "  root path : " << getRootPath().getPath();
	Logger::logger()->log(LOG_DEBUG, oss);

    oss << "  autoindex : " << getAutoIndex();
	Logger::logger()->log(LOG_DEBUG, oss);

	if (getHttpRedirection().getStatusCode() != 0)
	{
		oss << "  redirection : ";
		Logger::logger()->log(LOG_DEBUG, oss);

		oss << "    status code : " << getHttpRedirection().getStatusCode();
		Logger::logger()->log(LOG_DEBUG, oss);

		oss << "    uri : " << getHttpRedirection().getUri().getUri();
		Logger::logger()->log(LOG_DEBUG, oss);
	}

}

// =============================================================================
// Setters and Getters
// =============================================================================

// --- Setters ---

void	Location::setUri(Uri uri)
{
	uri_ = uri;
}

void	Location::setRootPath(Path rootPath)
{
	rootPath_ = rootPath;
}

void	Location::setAutoIndex(bool autoIndex)
{
	autoIndex_ = autoIndex;
}

void	Location::setHttpRedirection(HttpRedirection redirection)
{
	redirection_ = redirection;
}

void	Location::setDefaultFile(const Path& defaultFile)
{
	defaultFile_ = defaultFile;
}

void	Location::setUploadDirectory(const Path& uploadDirectory)
{
	uploadDirectory_ = uploadDirectory;
}

void	Location::setIsCgi(bool isCgi)
{
	isCgi_ = isCgi;
}

void	Location::setCgi(const Cgi& cgi)
{
	cgi_ = cgi;
}

void	Location::addAllowedMethod(HttpMethodType method)
{
	allowedMethods_.push_back(method);
}

// --- Getters ---

const Uri&	Location::getUri(void) const
{
	return (uri_);
}

const Path& 	Location::getRootPath(void) const
{
	return (rootPath_);
}

const std::string 	Location::getRootPathString(void) const
{
	return (rootPath_.getPath());
}

const HttpRedirection&	Location::getHttpRedirection(void) const
{
	return (redirection_);
}

bool	Location::getAutoIndex(void) const
{
	return (autoIndex_);
}

const Path&	Location::getDefaultFile(void) const
{
	return (defaultFile_);
}

const Path&	Location::getUploadDirectory(void) const
{
	return (uploadDirectory_);
}

bool	Location::getIsCgi(void) const
{
	return (isCgi_);
}

const Cgi&	Location::getCgi(void) const
{
	return (cgi_);
}

const std::vector<HttpMethodType>&	Location::getAllowedMethods(void) const
{
	return (allowedMethods_);
}

// =============================================================================
// Public Methods
// =============================================================================

bool	Location::isMethodAllowed(HttpMethodType method) const
{
	for (size_t i = 0; i != allowedMethods_.size(); ++i)
	{
		if (allowedMethods_[i] == method)
			return (true);
	}
	return (false);
}