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

// =============================================================================
// Setters and Getters
// =============================================================================

// --- Setters ---

void	Route::setUri(const Uri& uri)
{
	uri_ = uri;
}

void	Route::setRootPath(const Path& rootPath)
{
	rootPath_ = rootPath;
}

void	Route::setRedirection(const HttpRedirection& redirection)
{
	redirection_ = redirection;
}

void	Route::setAutoIndex(bool autoIndex)
{
	autoIndex_ = autoIndex;
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

const HttpRedirection&	Route::getRedirection(void) const
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