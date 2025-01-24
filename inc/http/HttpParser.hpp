#ifndef HTTP_PARSER_HPP
# define HTTP_PARSER_HPP

# include "HttpRequest.hpp"
# include <string>

class	HttpParser
{
	public:
		// --- Constructors and Destructor ---
						HttpParser(void);
						HttpParser(const HttpParser& other);

						HttpParser(std::string httpRequestRaw);

						~HttpParser(void);

		// --- Operators Overload ---
		HttpParser&		operator=(const HttpParser& rhs);

		HttpRequest		parse(void);

	private:
		// --- Private Attributes ---
		std::string		httpRequestRaw_;
		HttpRequest		httpRequest_;

		// --- Private Methods ---
		void			parseHttpRequestLine(void);
		void			parseHttpHeader(void);
};

#endif
