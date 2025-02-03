#ifndef HTTP_REQUEST_LINE_HPP
# define HTTP_REQUEST_LINE_HPP

# include "HttpMethodType.hpp"
# include "Path.hpp"
# include "Uri.hpp"

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
		void					setMethod(HttpMethodType httpMethod);

		const Uri&				getUri() const;
		void					setUri(Uri uri);

		const std::string&  	getHttpVersion() const;
		void					setHttpVersion(const std::string httpVersion);

		const std::string&  	getQueryString() const;
		void					setQueryString(const std::string queryString);

	private:
		// --- Private Attributes ---
        HttpMethodType      	method_;
        Uri						uri_;
        std::string         	httpVersion_;
        std::string         	queryString_; // example: /path?key=value

};

#endif
