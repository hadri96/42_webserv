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

		// --- Getters & Setters ---
		HttpMethodType      getMethod() const;
		std::string			getMethodString() const;
		const Uri&			getRelativeUri() const;
		const std::string&  getHttpVersion() const;
		const std::string&  getQueryString() const;

	private:
		// --- Private Attributes ---
        HttpMethodType      method_;
        Uri					relativeUri_;
        std::string         httpVersion_;
        std::string         queryString_; // example: /path?key=value

};

#endif
