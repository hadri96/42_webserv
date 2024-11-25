#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <vector>
# include <arpa/inet.h> 

# include "EventType.hpp"
# include "Manager.hpp"
# include "Client.hpp"

// --- Forward Declarations ---
class	Manager;

class	Server
{
	public:
		// --- Constructors and Destructor ---
								Server(void);

								Server(std::string host, int port, Manager* manager);

								Server(const Server& other);
								~Server(void);

		// --- Operators Overload ---
		Server&					operator=(const Server& rhs);
		bool					operator==(int fd);

		// --- Getters and Setters ---
		int						getFd(void) const;

		std::string				getInfoFd(void) const;
		std::string				getInfoUrl(void) const;
		std::string				getInfoHostPort(void) const;
	
		Client*					getClient(int fd) const;

		// --- Public Methods ---
		void					start(void);
		void					stop(void);

		void					handleEvent(EventType event);
		void					handleEvent(EventType event, int clientFd);

	private:
		// --- Private Attributes ---
		Manager*				manager_;

		int						fd_;
		std::string				host_;
		int						port_;

		struct sockaddr_in		address_;

		int						maxConnections_;
		std::vector<Client*>	clients_;

		// --- Private Methods ---
		void					registerClient(Client* client);
		void					unregisterClient(Client* client);

		void					acceptClient(void);
		void					handleClientRequest(int clientFd);
		void					sendClientResponse(int clientFd);
		void					closeClientConnection(int clientFd);
};

#endif
