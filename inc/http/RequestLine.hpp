#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <string>

# include "HttpMethodType.hpp"

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
