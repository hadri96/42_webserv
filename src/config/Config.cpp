#include "Config.hpp"

#include "Logger.hpp"

#include "ResourceDefault.hpp"

#include <sstream> // std::ostringstream
#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Config::Config(void) :
	host_("localhost"),
	port_(0),
	serverName_("default"),
	errorPages_(0),
	clientMaxBodySize_(-1),
	locations_(0)
{}

Config::Config(const Config& other) :
	host_(other.host_),
	port_(other.port_),
	serverName_(other.serverName_),
	errorPages_(other.errorPages_),
	redirection_(other.redirection_),
	clientMaxBodySize_(other.clientMaxBodySize_),
	locations_(other.locations_)
{}

Config::~Config(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Config&	Config::operator=(const Config& rhs)
{
	if (this == &rhs)
		return (*this);
	
	host_ = rhs.host_;
	port_ = rhs.port_;
	serverName_ = rhs.serverName_;
	errorPages_ = rhs.errorPages_;
	redirection_ = rhs.redirection_;
	clientMaxBodySize_ = rhs.clientMaxBodySize_;
	locations_ = rhs.locations_;

	return (*this);
}

/*std::ostream&	operator<<(std::ostream& os, Config& object)
{
	os << "### Config ###" << std::endl;
	os << "  server_name : " << object.getServerName() << std::endl;
	os << "  host : " << object.getHost() << std::endl;
	os << "  port : " << object.getPort() << std::endl;

	// Error pages
	for (size_t i = 0; i != object.getErrorPages().size(); ++i)
	{
		os << object.getErrorPages()[i];
	}
	os << "  client_max_body_size : " << object.getClientMaxBodySize() << std::endl;

	// Redirection
	os << object.getConfigRedirection();

	// Locations
	for (size_t i = 0; i != object.getLocations().size(); ++i)
	{
		os << object.getLocations()[i];
	}

	return (os);
}*/

void	Config::log(void)
{
	std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Generated configuration object");

	oss << "  server_name : " << getServerName();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  host : " << getHost();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  port : " << getPort();
	Logger::logger()->log(LOG_DEBUG, oss);

	// Error pages
	for (size_t i = 0; i != getConfigErrorPages().size(); ++i)
	{
		getConfigErrorPages()[i].display();
	}
	oss << "  client_max_body_size : " << getClientMaxBodySize();
	Logger::logger()->log(LOG_DEBUG, oss);

	// Redirection
	getConfigRedirection().log();

	// Locations
	for (size_t i = 0; i != getConfigLocations().size(); ++i)
	{
		getConfigLocations()[i].log();
		//Logger::logger()->log(LOG_DEBUG, oss);
	}
}

// =============================================================================
// Setters and Getters
// =============================================================================

// --- Setters ---

void	Config::setHost(const std::string& host)
{
	host_ = host;
}

void	Config::setPort(int port)
{
	port_ = port;
}

void	Config::setServerName(const std::string& serverName)
{
	serverName_ = serverName;
}

void	Config::setClientMaxBodySize(int clientMaxBodySize)
{
	clientMaxBodySize_ = clientMaxBodySize;
}

void	Config::setConfigRedirection(ConfigRedirection redirection)
{
	redirection_ = redirection;
}

void	Config::addConfigErrorPage(const ConfigErrorPage& errorPage)
{
	errorPages_.push_back(errorPage);
}

void	Config::addConfigLocation(const ConfigLocation& location)
{
	locations_.push_back(location);
}

// --- Getters ---

const std::string&	Config::getHost(void) const
{
	return (host_);
}

int	Config::getPort(void) const
{
	return (port_);
}

const std::string&	Config::getServerName(void) const
{
	return (serverName_);
}

ConfigRedirection&	Config::getConfigRedirection(void)
{
	return (redirection_);
}

int	Config::getClientMaxBodySize(void) const
{
	return (clientMaxBodySize_);
}

std::vector<ConfigErrorPage>&	Config::getConfigErrorPages(void)
{
	return (errorPages_);
}



// Function should get the correct route according to the uri: 
// Gets the substring between first and last slash of uriString and compares with config routes
// This needs to be adapted depending on what the routes look like in the config file
// It cannot be tested yet as we don't yet have multiple routes in our example Config

bool	Config::checkPathInConfig(Uri& uri, Path& outputPath) const
{
	std::string		uriString = uri;
	// Logger::logger()->log(LOG_DEBUG, "URI = " + uriString);

	for (size_t i = 0; i < locations_.size(); i++)
	{
		Logger::logger()->log(LOG_DEBUG, "Location = " + locations_[i].getRootPathString());
		Path	fullPath(locations_[i].getRootPathString() + uriString);
		if (fullPath.isInFileSystem())
		{	
			outputPath = fullPath;
			return (true);
		}
		Logger::logger()->log(LOG_DEBUG, "abs path in checkPathInConfig : " + fullPath.getAbsPath());
	}
	return (false);
}

std::vector<ConfigLocation>&	Config::getConfigLocations(void)
{
	return (locations_);
}

// =============================================================================
// Public Methods
// =============================================================================

const Path*	Config::getPath(Uri uri) const
{
	const ConfigLocation* foundLocation = getConfigLocation(uri);

	if (!foundLocation)
		return (0);

	return (&foundLocation->getRootPath());
}

// --- RequestInterpreter ---
bool	Config::isMethodAllowed(HttpMethodType method, Uri uri) const
{
	const ConfigLocation* location = getConfigLocation(uri);

	if (location)
		return (location->isMethodAllowed(method));

	if (method == POST  || method == GET)
		return (true);

	return (false);
}

bool	Config::isSizeAllowed(int byteSize, Uri uri) const
{
	(void) uri;
	(void) byteSize;

	return (true);
}

const ConfigErrorPage*	Config::getConfigErrorPage(int code) const
{
	for(size_t i = 0; i != errorPages_.size(); ++i)
	{
		if (errorPages_[i] == code)
			return (&errorPages_[i]);
	}
	return (0);
}

bool	Config::isTypeAllowed(HttpMimeType mimeType, Uri uri) const
{
	// Check in location then in main config if mime type is allowed
	(void) uri;
	
	if (mimeType)
		return (true);
	return (true);
}

std::string		Config::getCgiDir()
{
	// get the dir associated to CGI handling
	return ("/cgi_dir/");
}


// =============================================================================
// Private Methods
// =============================================================================

const ConfigLocation*	Config::getConfigLocation(Uri uri) const
{
	for (size_t i = 0; i != locations_.size(); ++i)
	{
		if (locations_[i] == uri || locations_[i] == ("=" + uri))
			return (&locations_[i]);
	}
	return (0);
}