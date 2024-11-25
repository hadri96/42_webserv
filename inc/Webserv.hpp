#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <string>

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
		// c
		// parseConfig(std::string File)
};

#endif