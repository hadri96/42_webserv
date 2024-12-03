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

const std::vector<Route>&	Config::getRoutes(void) const
{
	return (routes_);
}