#ifndef OBSERVER_HPP
# define OBSERVER_HPP

# include <sys/poll.h> // poll
# include <vector>

# include "HttpEventType.hpp"
# include "Server.hpp"

/*
 * Roles :
 * - Loads the configuration file and creates the servers accordingly
 * - Has a list of fds (both servers and clients) to monitor
 * - Handles new connections to servers
 * - Handles client events (POLLIN : the client send a request) (POLLOUT : the client is sent a response to)
 * - Monitors what is happening (display infos or logs informations)
 */

// --- Forward Declarations ---
class	Server;

class	Observer
{
	private:
		std::vector<pollfd> fds_;
		std::vector<Server*> servers_;

		bool				isServer(int fd);
		void				updatePollEvent(int clientFd, short newEvents);

		void				addSocketToMonitor(int fd, short events);
		void				removeSocketFromMonitor(int fd);

		Server*				getServerFromFd(int fd);

	public:
		// --- Public Methods ---

		// ··· Monitoring ···
		void				addServerToMonitor(Server* server);
		void				removeServerFromMonitor(Server* server);

		void				addClientToMonitor(int fd);
		void				removeClientFromMonitor(int fd);
		
		void				monitorEvents(void);
};

#endif
