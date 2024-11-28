#ifndef REQUESTLINE_HPP
# define REQUESTLINE_HPP

# include "HttpMethodType.hpp"
# include "Path.hpp"

# include <string>

class	RequestLine
{
	public:
		// --- Constructors and Destructor ---
					RequestLine(void);
					RequestLine(const RequestLine& other);

					~RequestLine(void);

		// --- Operators Overload ---
		RequestLine&		operator=(const RequestLine& other);

	private:
		// --- Private Attributes ---
        HttpMethodType      method_;
        Path                requestTarget_;
        std::string         httpVersion_;
        std::string         queryString_; // example: /path?key=value

};

#endif
