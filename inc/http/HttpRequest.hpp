#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "HttpRequestLine.hpp"
# include "HttpHeader.hpp"

# include <string>
# include <sstream>
# include <map>

class HttpRequest 
{
	public:
		// --- Constructors and Destructor ---
											HttpRequest();
											~HttpRequest();

		// --- Public Methods ---
		void                    			appendRequest(std::string input); // REVISIT : USELESS ?
		std::string             			generatePrintString();

		// --- Getters and Setters --- 
		const std::string&      			getRawRequest() const;

		// ··· Request Line ··· 
		const HttpRequestLine&  			getRequestLine() const; // REVISIT : USELESS ?

		HttpMethodType          			getMethod() const;
		void								setMethod(HttpMethodType httpMethod);

		const Uri&              			getUri() const;
		void								setUri(Uri uri);

		const std::string&					getHttpVersion(void) const;
		void								setHttpVersion(const std::string& httpVersion);

		// ··· Header ··· 
		const HttpHeader&       			getHttpHeader() const;  // REVISIT : USELESS ?

		HttpMimeType						getMimeType() const;

		// ··· Body ··· 
		const std::string&      			getBody() const;
		int                     			getBodySize() const;

		std::string							getInput(std::string key); // REVISIT : WHAT FOR ?

	private:
		// --- Private Attributes ---
		std::string             			rawRequest_; // REVISIT : USELESS ?

		HttpRequestLine         			requestLine_;
		HttpHeader             				header_;
		std::string             			body_;
		std::map<std::string, std::string>  inputs_;
};

#endif