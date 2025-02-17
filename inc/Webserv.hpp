#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <string>
#include <vector>

#include "Observer.hpp"
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
		Webserv&				operator=(const Webserv& rhs);

		// --- Public Methods ---
		void					start(void);
		void					destroy(void);

	private:
		// --- Private Attributes ---
		Observer* 				observer_;
		std::vector<Config> 	configs_;
		std::vector<Server*> 	servers_;

		// --- Private Methods ---
		Server*					getServer(const std::string& host, int port);
		void					checkForInvalidServer(void);

};

#endif