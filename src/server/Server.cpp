#include "Server.hpp"
#include "Logger.hpp"
#include "ToString.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "RequestInterpreter.hpp"

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h> // sockaddr_in
#include <fcntl.h> // fcntl
#include <unistd.h> // close
#include <cerrno>

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

Server::Server(std::string host, int port, Observer* observer) :
	observer_(observer),
	fd_(0),
	host_(host),
	port_(port),
	maxConnections_(1024)
{
	Logger::logger()->log(LOG_INFO, "Created a server block " + getInfoHostPort());
}

/*Server::Server(const Config& config, Observer* observer)
{}*/

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

void	Server::setConfig(Config& config)
{
	config_ = config;
}

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
	int			temp = 1;

	addressLen_ = sizeof(address_);
	// --- Socket ---
	fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_ == -1)
	{
		// To handle with exceptions
		Logger::logger()->log(LOG_ERROR, "Socket creation failed");
	}
	// Logger::logger()->log(LOG_INFO, "Created a server socket " + getInfoFd());

	// --- Bind ---

	address_.sin_family = AF_INET;
	address_.sin_addr.s_addr = inet_addr(host_.c_str());
	address_.sin_port = htons(port_);

    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) < 0) 
    {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        exit(EXIT_FAILURE);
    }

	if (bind(fd_, (struct sockaddr *)&address_, addressLen_) < 0)
	{
		Logger::logger()->log(LOG_ERROR, "Bind failed");
		stop();
	}

	// --- Listen ---
	if (listen(fd_, maxConnections_) < 0)
	{
		Logger::logger()->log(LOG_ERROR, "Listen failed");
		stop();
	}

	if (fcntl(fd_, F_SETFL, O_NONBLOCK | FD_CLOEXEC) == -1) 
	{
		std::cerr << "fcntl " << fd_ << " failed: " << strerror(errno) << std::endl;
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
		fd_ = -1;
	}
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
			Logger::logger()->log(LOG_INFO, "CLIENT_NEW_CONNECTION");
			acceptClient();
			break ;
		case CLIENT_SENDING_REQUEST:
			Logger::logger()->log(LOG_INFO, "CLIENT_SENDING_REQUEST");
			handleRequestFromClient(clientFd);
			break ;
		case CLIENT_EXPECTING_RESPONSE:
			Logger::logger()->log(LOG_INFO, "CLIENT_EXPECTING_RESPONSE");
			sendResponseToClient(clientFd);
			break ;
		case CLIENT_ERROR:
			closeClientConnection(clientFd, "CLIENT_ERROR");
			break ;
		case CLIENT_DISCONNECTED:
			closeClientConnection(clientFd, "CLIENT_DISCONNECTED");
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
	socklen_t	addressLen_;
	int 		clientFd;
	char		clientIp[INET_ADDRSTRLEN];
	int			clientPort;


	addressLen_ = sizeof(address_);
	clientFd = accept(fd_, (struct sockaddr*)&address_, (socklen_t *)&addressLen_);

	observer_->addClientToMonitor(clientFd);

	if (clientFd < 0)
	{
		Logger::logger()->log(LOG_ERROR, "Accept failed");
		stop();
	}

	inet_ntop(AF_INET, &address_.sin_addr, clientIp, sizeof(clientIp));
	clientPort = ntohs(address_.sin_port);

	registerClient(new Client(clientFd, clientIp, clientPort));
}

// --- handleClientRead ---
// -> interprete la requete du client et l'ajoute au client->httpRequest
void	Server::handleRequestFromClient(int clientFd)
{
    char                buffer[1024] = {0};
    int                 bytesRead;
    Client              *client = getClient(clientFd);
    HttpRequest         request;
    
    client->assignRequest(request);
    
    while ((bytesRead = recv(clientFd, buffer, sizeof(buffer) -1, 0)) > 0)
    {
        request.appendRequest(buffer);
        if (request.getRawRequest().find("\r\n\r\n") != std::string::npos)
			break ;
    }
	Logger::logger()->log(LOG_DEBUG, "Request looks like this: \n" + request.getRawRequest());
	if (bytesRead < 0)
		closeClientConnection(clientFd, "read error");
	runInterpreter(request, clientFd);
}

void	Server::runInterpreter(HttpRequest& request, int clientFd)
{
	RequestInterpreter 	interpreter = RequestInterpreter(this);
	Client* 			client = getClient(clientFd);

	Logger::logger()->log(LOG_DEBUG, "Run Interpreter");
	try 
	{
		HttpResponse response = interpreter.interpret(request, config_);
		client->assignResponse(response);
	}
	catch (std::exception& e)
	{
		Logger::logger()->log(LOG_ERROR, e.what());
	}
}

// --- sendResponseBuffer et handleClientWrite ---

void    Server::sendResponseToClient(int clientFd)
{
	std::string		fullResponse = getClient(clientFd)->getResponseString();
	size_t			bufferSize = 1024;
    size_t			totalSize = fullResponse.size();
    size_t			bytesSent = 0;

	Logger::logger()->log(LOG_DEBUG, "sendResponseToClient");
	Logger::logger()->log(LOG_DEBUG, fullResponse);
    while (bytesSent < totalSize) 
    {
        size_t      chunkSize = std::min(bufferSize, totalSize - bytesSent);
        int         sent;
        
        sent = send(clientFd, (fullResponse.c_str() + bytesSent), chunkSize, 0);
        if (sent < 0) 
        {
            closeClientConnection(clientFd, "Error in send() function.");
            return;
        }
        bytesSent += sent;
    }
}

void	Server::closeClientConnection(int clientFd, std::string message)
{
	unregisterClient(getClient(clientFd));
	observer_->removeClientFromMonitor(clientFd);
	Logger::logger()->log(LOG_DEBUG, "Closing client connection [fd = " + toString(clientFd) + "] : " + message);
	close(clientFd);
}