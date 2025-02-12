#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <string>
#include <vector>

#include "Config.hpp"
#include "Server.hpp"

class	Webserv
{
	public:
		// --- Constructors and Destructor ---
					Webserv(void);

					Webserv(const std::string& configFile);

					Webserv(const Webserv& other);
					~Webserv(void);

		// --- Operators Overload ---
		Webserv&	operator=(const Webserv& rhs);

		// --- Public Methods ---
		void		start(void);
	private:
		// --- Private Attributes ---
		std::vector<Config> 	configs_;
		std::vector<Server*> 	servers_;

		// --- Private Methods ---
		Server*		getServer(const std::string& host, int port);

};

#endif