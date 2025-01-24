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
		void                    			appendRequest(std::string input);
		std::string             			generatePrintString();
		
	// ··· "Deep" Getters and utils ···  
		const std::string       			getRelativeUri() const;
		HttpMethodType          			getMethod() const;

	// ··· Direct getters ···  
		const std::string&      			getRawRequest() const;
		const HttpRequestLine&  			getRequestLine() const;
		const HttpHeader&       			getHttpHeader() const;
		const std::string&      			getBody() const;
		int                     			getBodySize() const;
		const Uri&              			getUri() const;
		HttpMimeType						getMimeType() const;
		std::string							getInput(std::string key);

	private:
	// --- Private Attributes ---
		std::string             			rawRequest_;

		HttpRequestLine         			requestLine_;
		HttpHeader             				header_;
		std::string             			body_;
		std::map<std::string, std::string>  inputs_;
};

#endif