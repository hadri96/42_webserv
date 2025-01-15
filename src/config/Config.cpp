#include "Config.hpp"

#include "Logger.hpp"
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
	Locations_(0)
{}

Config::Config(const Config& other) :
	host_(other.host_),
	port_(other.port_),
	serverName_(other.serverName_),
	errorPages_(other.errorPages_),
	redirection_(other.redirection_),
	clientMaxBodySize_(other.clientMaxBodySize_),
	Locations_(other.Locations_)
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
	Locations_ = rhs.Locations_;

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
	os << object.getHttpRedirection();

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
	for (size_t i = 0; i != getErrorPages().size(); ++i)
	{
		oss << getErrorPages()[i];
		Logger::logger()->log(LOG_DEBUG, oss);
	}
	oss << "  client_max_body_size : " << getClientMaxBodySize();
	Logger::logger()->log(LOG_DEBUG, oss);

	// Redirection
	getHttpRedirection().log();

	// Locations
	for (size_t i = 0; i != getLocations().size(); ++i)
	{
		getLocations()[i].log();
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

void	Config::setHttpRedirection(HttpRedirection redirection)
{
	redirection_ = redirection;
}

void	Config::addErrorPage(const ErrorPage& errorPage)
{
	errorPages_.push_back(errorPage);
}

void	Config::addLocation(const Location& Location)
{
	Locations_.push_back(Location);
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

HttpRedirection&	Config::getHttpRedirection(void)
{
	return (redirection_);
}

int	Config::getClientMaxBodySize(void) const
{
	return (clientMaxBodySize_);
}

std::vector<ErrorPage>&	Config::getErrorPages(void)
{
	return (errorPages_);
}

const ErrorPage	Config::getErrorPage(int statusCode)
{
	for( std::vector<ErrorPage>::const_iterator it = errorPages_.begin(); it != errorPages_.end(); it++)
	{
		if (it->getErrorCode() == statusCode)
			return (*it);
	}
	return (ErrorPage());
}

// Function should get the correct Location according to the uri: 
// Gets the substring between first and last slash of uriString and compares with config Locations
// This needs to be adapted depending on what the Locations look like in the config file
// It cannot be tested yet as we don't yet have multiple Locations in our example Config
const Path&	Config::getPathFromUri(Uri& uri) const
{
	std::string		uriString = uri.getUri(); 
	std::string		LocationSegment;
	size_t			firstSlash = uriString.find('/');
	size_t			lastSlash = uriString.rfind('/');

	if (lastSlash != std::string::npos)
		LocationSegment = uriString.substr(firstSlash + 1, lastSlash - firstSlash - 1);
	else if (firstSlash != std::string::npos)
		LocationSegment = uriString.substr(firstSlash + 1);
	else
		LocationSegment = "";

	for (std::vector<Location>::const_iterator it = Locations_.begin(); it != Locations_.end(); it++)
	{
		if (it->getRootPathString() == LocationSegment)
			return ((*it).getRootPath());
	}
	return (Locations_[0].getRootPath());
}


std::vector<Location>&	Config::getLocations(void)
{
	return (Locations_);
}
