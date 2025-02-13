#include "Client.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Client::Client(void) : fd_(0), ip_("0.0.0.0"), port_(0), currentRequest_(HttpRequest()), currentResponse_(HttpResponse())
{}

Client::Client(int fd, std::string ip, int port) : fd_(fd), ip_(ip), port_(port), currentRequest_(HttpRequest()), currentResponse_(HttpResponse())
{}

Client::Client(const Client& other) : fd_(other.fd_), ip_(other.ip_), port_(other.port_), currentRequest_(HttpRequest()), currentResponse_(HttpResponse())
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

HttpRequest		Client::getCurrentRequest(void) const
{
    return (currentRequest_);
}

HttpResponse	Client::getCurrentResponse(void) const
{
    return (currentResponse_);
}

std::string	Client::getResponseString(void) const
{
	return (currentResponse_.getFullResponse());
}


// =============================================================================
// Public Methods
// =============================================================================

void	Client::assignRequest(HttpRequest request)
{
	currentRequest_ = request;
}

void	Client::assignResponse(HttpResponse response)
{
	currentResponse_ = response;
}
