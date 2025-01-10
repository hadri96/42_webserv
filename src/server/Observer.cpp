#include <iostream>

#include "Observer.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

// =============================================================================
// Operators Overload
// =============================================================================

// =============================================================================
// Public Methods
// =============================================================================

void	Observer::addServerToMonitor(Server* server)
{
	addSocketToMonitor(server->getFd(), POLLIN | POLLOUT);
	servers_.push_back(server);
	Logger::logger()->log(LOG_INFO, "Server added to monitor " + server->getInfoFd());
}

void	Observer::removeServerFromMonitor(Server* server)
{
	removeSocketFromMonitor(server->getFd());
	Logger::logger()->log(LOG_INFO, "Server removed from monitor " + server->getInfoFd());
}

void	Observer::addClientToMonitor(int fd)
{
	addSocketToMonitor(fd, POLLIN | POLLOUT);
	Logger::logger()->log(LOG_INFO, "Client added to monitor [fd = " + toString(fd) + "]");
}

void	Observer::removeClientFromMonitor(int fd)
{
	removeSocketFromMonitor(fd);
	Logger::logger()->log(LOG_INFO, "Client removed from monitor [fd = " + toString(fd) + "]");
}

void	Observer::monitorEvents(void)
{
	while (true)
	{
		int count = poll(fds_.data(), fds_.size(), -1);
		
		if (count < 0)
		{
			Logger::logger()->log(LOG_ERROR, "Polling error");
			break;
		}

		for (size_t i = 0; i < fds_.size(); ++i)
		{
			if (fds_[i].revents == 0)
				continue ;
			if (isServer(fds_[i].fd))
			{
				if (fds_[i].revents & POLLIN)
					getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_NEW_CONNECTION);
			}
			else
			{
				if (fds_[i].revents & POLLIN)
				{	
					Logger::logger()->log(LOG_DEBUG, toString(fds_[i].fd) + " is POLLIN");
					getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_SENDING_REQUEST, fds_[i].fd);
					updatePollEvent(fds_[i].fd, POLLOUT);
					if (fds_[i].revents & POLLOUT)
					{	
						getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_EXPECTING_RESPONSE, fds_[i].fd);
						updatePollEvent(fds_[i].fd, POLLIN);
					}
				}
				// 	Logger::logger()->log(LOG_WARNING, toString(fds_[i].fd) + " is POLLOUT");
				// else if (fds_[i].revents & POLLHUP)
				// 	getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_DISCONNECTED, fds_[i].fd);
				// else if (fds_[i].revents & POLLERR)
				// 	getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_ERROR, fds_[i].fd);
			}
		}
	}
}


// =============================================================================
// Private Methods
// =============================================================================

void	Observer::updatePollEvent(int clientFd, short newEvents)
{
	for (std::size_t i = 0; i < fds_.size(); i++)
	{
		if (fds_[i].fd == clientFd)
		{
			fds_[i].events = newEvents;
			Logger::logger()->log(LOG_INFO, "Updated events for FD " + toString(clientFd) + " to " + toString(newEvents));
		}
	}
}


bool	Observer::isServer(int fd)
{
	for (size_t i = 0; i < servers_.size(); ++i)
	{
		if (*servers_[i] == fd)
			return (true);
	}
	return (false);
}

void	Observer::addSocketToMonitor(int fd, short events)
{
	struct pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;

	fds_.push_back(pfd);
}

void	Observer::removeSocketFromMonitor(int fd)
{
	for (std::vector<pollfd>::iterator it = fds_.begin(); it != fds_.end(); ++it)
	{
		if (it->fd == fd)
		{
			fds_.erase(it);
			break ;
		}
	}
}

Server*	Observer::getServerFromFd(int fd)
{
	if (isServer(fd))
	{
		for (size_t i = 0; i < servers_.size(); ++i)
		{
			if (*servers_[i] == fd)
				return (servers_[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < servers_.size(); ++i)
		{
			if (servers_[i]->getClient(fd) != 0)
				return (servers_[i]);
		}
	}
	return (0);
}