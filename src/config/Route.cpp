#include "Route.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Route::Route(void) :
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

Route::Route(const Route& other) :
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
Route::~Route(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Route&	Route::operator=(const Route& rhs)
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

/*std::ostream&	operator<<(std::ostream& os, Route& object)
{
	os << "--- Route ---" << std::endl;
	os << "  uri : " << object.getUri().getUri() << std::endl;
	os << "  root path : " << object.getRootPath().getPath() << std::endl;
	os << "  autoindex : " << object.getAutoIndex() << std::endl;
	
	// limit except ?
	return (os);
}*/

/*
std::ostream& operator<<(std::ostream& os, Route& object) {
    std::ostringstream oss;

    oss << "--- Route ---" << std::endl;
    oss << "  uri : " << object.getUri().getUri() << std::endl;
    oss << "  root path : " << object.getRootPath().getPath() << std::endl;
    oss << "  autoindex : " << object.getAutoIndex() << std::endl;

    Logger::logger()->log(LOG_DEBUG, oss.str()); // Log the message with the prefix
    
    // No longer output to 'os' here; remove os << oss.str();

    return os;
}
*/

void	Route::log(void)
{
    std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Route", 2);

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

void	Route::setUri(Uri uri)
{
	uri_ = uri;
}

void	Route::setRootPath(Path rootPath)
{
	rootPath_ = rootPath;
}

void	Route::setAutoIndex(bool autoIndex)
{
	autoIndex_ = autoIndex;
}

void	Route::setHttpRedirection(HttpRedirection redirection)
{
	redirection_ = redirection;
}

void	Route::setDefaultFile(const Path& defaultFile)
{
	defaultFile_ = defaultFile;
}

void	Route::setUploadDirectory(const Path& uploadDirectory)
{
	uploadDirectory_ = uploadDirectory;
}

void	Route::setIsCgi(bool isCgi)
{
	isCgi_ = isCgi;
}

void	Route::setCgi(const Cgi& cgi)
{
	cgi_ = cgi;
}

void	Route::addAllowedMethod(HttpMethodType method)
{
	allowedMethods_.push_back(method);
}

// --- Getters ---

const Uri&	Route::getUri(void) const
{
	return (uri_);
}

const Path& 	Route::getRootPath(void) const
{
	return (rootPath_);
}

const std::string 	Route::getRootPathString(void) const
{
	return (rootPath_.getPath());
}

const HttpRedirection&	Route::getHttpRedirection(void) const
{
	return (redirection_);
}

bool	Route::getAutoIndex(void) const
{
	return (autoIndex_);
}

const Path&	Route::getDefaultFile(void) const
{
	return (defaultFile_);
}

const Path&	Route::getUploadDirectory(void) const
{
	return (uploadDirectory_);
}

bool	Route::getIsCgi(void) const
{
	return (isCgi_);
}

const Cgi&	Route::getCgi(void) const
{
	return (cgi_);
}

const std::vector<HttpMethodType>&	Route::getAllowedMethods(void) const
{
	return (allowedMethods_);
}