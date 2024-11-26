#ifndef HTTP_REDIRECTION_HPP
# define HTTP_REDIRECTION_HPP

# include "Path.hpp"

class	HttpRedirection
{
	public:
		// --- Constructors and Destructor ---
							HttpRedirection(void);
							HttpRedirection(const HttpRedirection& other);

							~HttpRedirection(void);

		// --- Operators Overload ---
		HttpRedirection&	operator=(const HttpRedirection& rhs);

	private:
		// --- Private Attributes ---
		int					statusCode_;
		Path				path_;
};

#endif
