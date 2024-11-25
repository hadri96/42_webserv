#include "Client.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Client::Client(void) : fd_(0), ip_("0.0.0.0"), port_(0)
{}

Client::Client(int fd, std::string ip, int port) : fd_(fd), ip_(ip), port_(port)
{}

Client::Client(const Client& other) : fd_(other.fd_), ip_(other.ip_), port_(other.port_)
{}

Client::~Client(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Client&	Client::operator=(const Client& rhs)
{
	(void) rhs;
	return (*this);
}

bool	Client::operator==(int fd)
{
	return (fd_ == fd);
}

// =============================================================================
// Getters and Setters
// =============================================================================

int		Client::getFd(void) const
{
	return (fd_);
}