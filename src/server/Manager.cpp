#include <iostream>

#include "Manager.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

// =============================================================================
// Operators Overload
// =============================================================================

// =============================================================================
// Private Methods
// =============================================================================

bool	Manager::isServer(int fd)
{
	for (size_t i = 0; i < servers_.size(); ++i)
	{
		if (*servers_[i] == fd)
			return (true);
	}
	return (false);
}

void	Manager::addSocketToMonitor(int fd, short events)
{
	struct pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;

	fds_.push_back(pfd);
}

void	Manager::removeSocketFromMonitor(int fd)
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

Server*	Manager::getServerFromFd(int fd)
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

// =============================================================================
// Public Methods
// =============================================================================

void	Manager::addServerToMonitor(Server* server)
{
	addSocketToMonitor(server->getFd(), POLLIN | POLLOUT);
	servers_.push_back(server);
	Logger::logger()->log(LOG_INFO, "Server added to monitor " + server->getInfoFd());
}

void	Manager::removeServerFromMonitor(Server* server)
{
	removeSocketFromMonitor(server->getFd());
	Logger::logger()->log(LOG_INFO, "Server removed from monitor " + server->getInfoFd());
}

void	Manager::addClientToMonitor(int fd)
{
	addSocketToMonitor(fd, POLLIN | POLLOUT);
	Logger::logger()->log(LOG_INFO, "Client added to monitor [fd = " + toString(fd) + "]");
}

void	Manager::removeClientFromMonitor(int fd)
{
	removeSocketFromMonitor(fd);
	Logger::logger()->log(LOG_INFO, "Client removed from monitor [fd = " + toString(fd) + "]");
}

void	Manager::monitorEvents(void)
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
					getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_SENDING_REQUEST, fds_[i].fd); ///
				else if (fds_[i].revents & POLLHUP)
					getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_DISCONNECTED, fds_[i].fd);
				else if (fds_[i].revents & POLLOUT)
					getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_EXPECTING_RESPONSE, fds_[i].fd);
				else if (fds_[i].revents & POLLERR)
					getServerFromFd(fds_[i].fd)->handleEvent(CLIENT_ERROR, fds_[i].fd);
			}
		}
	}
}