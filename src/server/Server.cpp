#include "Server.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in
#include <fcntl.h> // fcntl
#include <unistd.h> // close

#include <string>
#include <cstring> // strlen

#include <stdlib.h> // exit ; MUST BE REMOVED LATER

// =============================================================================
// Constructors and Destructor
// =============================================================================

Server::Server(void) : 
	fd_(0),
	host_("0.0.0.0"),
	port_(80),
	maxConnections_(1024)
{}

Server::Server(const Server& other) : 
	fd_(other.fd_), 
	host_(other.host_), 
	port_(other.port_),
	address_(other.address_),
	maxConnections_(other.maxConnections_)
{}

Server::Server(std::string host, int port, Manager* manager) :
	manager_(manager),
	fd_(0),
	host_(host),
	port_(port),
	maxConnections_(1024)
{
	Logger::logger()->log(LOG_INFO, "Created a server block " + getInfoHostPort());
}

Server::~Server(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Server&	Server::operator=(const Server& rhs)
{
	(void) rhs;
	return (*this);
}

bool	Server::operator==(int fd)
{
	return (fd_ == fd);
}


// =============================================================================
// Getters and Setters
// =============================================================================

int	Server::getFd(void) const
{
	return (fd_);
}

std::string	Server::getInfoFd(void) const
{
	return ("[fd = " + toString(fd_) + "]");
}

std::string	Server::getInfoHostPort(void) const
{
	return ("[" + host_ + ":" + toString(port_) + "]");
}

std::string	Server::getInfoUrl(void) const
{
	return ("[http://" + host_ + ":" + toString(port_) + "]");
}

Client*	Server::getClient(int fd) const
{
	for (size_t i = 0; i != clients_.size(); ++i)
	{
		if (*clients_[i] == fd)
			return (clients_[i]);
	}
	return (0);
}

// =============================================================================
// Public Methods
// =============================================================================

void	Server::start(void)
{
	socklen_t	addressLen_;

	addressLen_ = sizeof(address_);
	// --- Socket ---
	fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_ == -1)
	{
		// To handle with exceptions
		Logger::logger()->log(LOG_ERROR, "Socket creation failed");
	}
	Logger::logger()->log(LOG_INFO, "Created a server socket " + getInfoFd());

	// --- Bind ---

	address_.sin_family = AF_INET;
	address_.sin_addr.s_addr = inet_addr(host_.c_str());
	address_.sin_port = htons(port_);

	if (bind(fd_, (struct sockaddr *)&address_, addressLen_) < 0)
	{
		Logger::logger()->log(LOG_ERROR, "Bind failed");
		stop();
	}
	Logger::logger()->log(LOG_INFO, "Bound successfully " + getInfoUrl());

	// --- Listen ---
	if (listen(fd_, maxConnections_) < 0)
	{
		// To handle with exceptions
		Logger::logger()->log(LOG_ERROR, "Listen failed");
		stop();
	}
	Logger::logger()->log(LOG_INFO, "Server is listening for connections...");

	// Set O_NONBLOCK and FD_CLOEXEC (close on exec) flags at the same time using F_SETFL
	if (fcntl(fd_, F_SETFL, O_NONBLOCK | FD_CLOEXEC) == -1) 
	{
		std::cerr << "fcntl failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Server::stop(void)
{
	// --- Close ---
	if (fd_ != -1)
	{
		Logger::logger()->log(LOG_INFO, "Stopping server, closing socket " + getInfoFd());
		close(fd_);
		fd_ = -1;  // Reset the fd
	}
	//exit (0);
}

void	Server::handleEvent(EventType event)
{
	handleEvent(event, -1);
}

void	Server::handleEvent(EventType event, int clientFd)
{
	(void) clientFd;
	switch (event)
	{
		case CLIENT_NEW_CONNECTION:
			acceptClient();
			break ;
		case CLIENT_READY_TO_READ:
			handleClientRequest(clientFd);
			break ;
		case CLIENT_READY_TO_WRITE:
			sendClientResponse(clientFd);
			break ;
		case CLIENT_ERROR:
			std::cout << "CLIENT_ERROR" << std::endl;
			closeClientConnection(clientFd);
			break ;
		case CLIENT_DISCONNECTED:
			std::cout << "CLIENT_DISCONNECTED" << std::endl;
			closeClientConnection(clientFd);
			break ;
	}
}

// =============================================================================
// Private Methods
// =============================================================================

void	Server::registerClient(Client* client)
{
	clients_.push_back(client);
}

void	Server::unregisterClient(Client* client)
{
	if (client)
	{
		delete client;
		for (std::vector<Client*>::iterator it = clients_.begin(); it != clients_.end(); ++it)
		{
			if (*it == client)
			{
				clients_.erase(it);
				break ;
			}
		}
	}
}

void	Server::acceptClient(void)
{
	std::cout << "acceptClient" << std::endl;
	socklen_t	addressLen_;
	int 		clientFd;
	char		clientIp[INET_ADDRSTRLEN];
	int			clientPort;


	addressLen_ = sizeof(address_);
	clientFd = accept(fd_, (struct sockaddr*)&address_, (socklen_t *)&addressLen_);

	manager_->addClientToMonitor(clientFd);

	if (clientFd < 0)
	{
		Logger::logger()->log(LOG_ERROR, "Accept failed");
		stop();
	}

	inet_ntop(AF_INET, &address_.sin_addr, clientIp, sizeof(clientIp));
	clientPort = ntohs(address_.sin_port);

	registerClient(new Client(clientFd, clientIp, clientPort));
	Logger::logger()->log(LOG_INFO, "Client connected to server");
}

void	Server::sendClientResponse(int clientFd)
{
	std::cout << "sendClientResponse" << std::endl;
	const char	*response = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 46\r\n"
		"\r\n"
		"<html><body><h1>Hello, World!</h1></body></html>";
	
	write(clientFd, response, strlen(response));
}

void	Server::handleClientRequest(int clientFd)
{
	std::cout << "handleClientRequest" << std::endl;
	(void) clientFd;
}

void	Server::closeClientConnection(int clientFd)
{
	std::cout << "closeClientConnection" << std::endl;
	unregisterClient(getClient(clientFd));
	manager_->removeClientFromMonitor(clientFd);
	Logger::logger()->log(LOG_INFO, "Closing client connection [fd = " + toString(clientFd) + "]");
	
	close(clientFd);
}
