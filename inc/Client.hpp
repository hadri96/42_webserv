#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include <string>

class	Client
{
	public:
		// --- Constructors and Destructor ---
						Client(void);

						Client(int fd, std::string ip, int port);

						Client(const Client& other);
						~Client(void);

		// --- Operators Overload ---
		Client&			operator=(const Client& rhs);
		bool			operator==(int fd);

		// --- Getters and Setters ---
		int				getFd(void) const;
		HttpResponse*	getCurrentResponse(void) const;
        HttpRequest*	getCurrentRequest(void) const;

		// --- Public Methods ---
		void			assignRequest(HttpRequest *request);
		void			assignResponse(HttpResponse *response);

	private:
		// --- Private Attributes ---
		int				fd_;
		std::string		ip_;
		int				port_;

		HttpRequest*	currentRequest_;
		HttpResponse*	currentResponse_;

};

#endif