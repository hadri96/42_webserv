#ifndef HTTP_REQUEST_LINE_HPP
# define HTTP_REQUEST_LINE_HPP

# include "HttpMethodType.hpp"
# include "Path.hpp"

# include <string>

class	HttpRequestLine
{
	public:
		// --- Constructors and Destructor ---
								HttpRequestLine(void);
								HttpRequestLine(const HttpRequestLine& other);

								~HttpRequestLine(void);

		// --- Operators Overload ---
		HttpRequestLine&		operator=(const HttpRequestLine& other);

		// --- Getters & Setters ---
		HttpMethodType      	getMethod() const;
		std::string				getMethodString() const;
		const Uri&				getRelativeUri() const;
		const std::string&  	getHttpVersion() const;
		const std::string&  	getQueryString() const;

	private:
		// --- Private Attributes ---
        HttpMethodType      	method_;
        Uri						relativeUri_;
        std::string         	httpVersion_;
        std::string         	queryString_; // example: /path?key=value

};

#endif
