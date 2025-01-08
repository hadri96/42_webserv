#include "Config.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Config::Config(void) :
	host_("localhost"),
	port_(0),
	serverName_("default"),
	errorPages_(0),
	clientMaxBodySize_(-1),
	routes_(0)
{}

Config::Config(const Config& other) :
	host_(other.host_),
	port_(other.port_),
	serverName_(other.serverName_),
	errorPages_(other.errorPages_),
	clientMaxBodySize_(other.clientMaxBodySize_),
	routes_(other.routes_)
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
	clientMaxBodySize_ = rhs.clientMaxBodySize_;
	routes_ = rhs.routes_;

	return (*this);
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

void	Config::setRedirection(const HttpRedirection& redirection)
{
	redirection_ = redirection;
}

void	Config::addErrorPage(const ErrorPage& errorPage)
{
	errorPages_.push_back(errorPage);
}

void	Config::addRoute(const Route& route)
{
	routes_.push_back(route);
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

int	Config::getClientMaxBodySize(void) const
{
	return (clientMaxBodySize_);
}

const std::vector<ErrorPage>&	Config::getErrorPages(void) const
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

const std::vector<Route>&	Config::getRoutes(void) const
{
	return (routes_);
}

// Function should get the correct route according to the uri: 
// Gets the substring between first and last slash of uriString and compares with config routes
// This needs to be adapted depending on what the routes look like in the config file
// It cannot be tested yet as we don't yet have multiple routes in our example Config
const Path&	Config::getPathFromUri(Uri& uri) const
{
	std::string		uriString = uri.getUri(); 
	std::string		routeSegment;
	size_t			firstSlash = uriString.find('/');
	size_t			lastSlash = uriString.rfind('/');

	if (lastSlash != std::string::npos)
		routeSegment = uriString.substr(firstSlash + 1, lastSlash - firstSlash - 1);
	else if (firstSlash != std::string::npos)
		routeSegment = uriString.substr(firstSlash + 1);
	else
		routeSegment = "";

	for (std::vector<Route>::const_iterator it = routes_.begin(); it != routes_.end(); it++)
	{
		if (it->getRootPathString() == routeSegment)
			return ((*it).getRootPath());
	}
	return (routes_[0].getRootPath());
}
