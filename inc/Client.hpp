#ifndef CLIENT_HPP
# define CLIENT_HPP

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
		Client&		operator=(const Client& rhs);
		bool		operator==(int fd);

		// --- Getters and Setters ---
		int			getFd(void) const;

	private:
		// --- Private Attributes ---
		int			fd_;
		std::string	ip_;
		int			port_;
};

#endif
