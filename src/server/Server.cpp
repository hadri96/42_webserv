#include "Server.hpp"
#include "Logger.hpp"
#include "ToString.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

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
	Logger::logger()->log(LOG_INFO, "Created a server socket " + getInfoFd());

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
			Logger::logger()->log(LOG_ERROR, "CLIENT_ERROR");
			closeClientConnection(clientFd);
			break ;
		case CLIENT_DISCONNECTED:
			Logger::logger()->log(LOG_INFO, "CLIENT_DISCONNECTED");
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
	Logger::logger()->log(LOG_INFO, "Server::acceptClient called");
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
	Logger::logger()->log(LOG_INFO, "Client connected to server");
}

// --- handleClientRead ---
// -> interprete la requete du client et l'ajoute au client->httpRequest
void	Server::handleRequestFromClient(int clientFd)
{
	Logger::logger()->log(LOG_INFO, "Server::handleRequestFromClient called");
    char                buffer[1024] = {0};
    int                 bytesRead;
    Client              *client = getClient(clientFd);
    HttpRequest         request;
    
    client->assignRequest(&request); 
    
    while ((bytesRead = read(clientFd, buffer, sizeof(buffer))) > 0)
    {
        request.appendRequest(buffer);

        if (request.getRawRequest().find("\r\n\r\n") != std::string::npos)
        {
            std::cout << "HTTP Request saved here:\n" << request.getRawRequest() << "\nEND OF REQUEST" << std::endl;
			/*
            HttpResponse    response;
			*/

            /*
            Here we need a series of functions that parse the request 
            then create a response based on the request and on the ServerConfig values for that socket
            (according to method type, error response codes etc.)

            something like:
                request.parsing();
                response.generateResponse(&request);
            */
            
			/*
			client->assignResponse(&response);
            sendResponseBuffer(clientFd, client->getCurrentResponse());
            break;
			*/
			break ;
        }
    }
	/*
    if (bytesRead == 0)
        //closeClientConnection(i, "Client disconnected: bytesRead = 0");
		closeClientConnection(clientFd);
    else if (bytesRead < 0)
        //closeClientConnection(i, "Client disconnected due to read error (bytesRead = -1)");
		closeClientConnection(clientFd);*/
}

// en fonction de client->httpRequest construire client->httpResponse

// --- sendResponseBuffer et handleClientWrite ---

void    Server::sendResponseToClient(int clientFd)
{
	Logger::logger()->log(LOG_INFO, "Server::sendResponseToClient called");
	HttpResponse    response;
   	std::string     body = response.getResponse("example_response.html");
    size_t          bufferSize = 1024;
    size_t          totalSize = body.size();
    size_t          bytesSent = 0;

    while (bytesSent < totalSize) 
    {
        size_t      chunkSize = std::min(bufferSize, totalSize - bytesSent);
        int         sent;
        
        sent = send(clientFd, (body.c_str() + bytesSent), chunkSize, 0);
        if (sent < 0) 
        {
            closeClientConnection(clientFd);
            return;
        }
        bytesSent += sent;
    }
    Logger::logger()->log(LOG_INFO, "Response sent in chunks");
	closeClientConnection(clientFd);
}

void	Server::closeClientConnection(int clientFd)
{
	unregisterClient(getClient(clientFd));
	observer_->removeClientFromMonitor(clientFd);
	Logger::logger()->log(LOG_INFO, "Closing client connection [fd = " + toString(clientFd) + "]");
	
	close(clientFd);
}