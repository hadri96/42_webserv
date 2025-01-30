#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "HttpRequestLine.hpp"

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
		void								log();

		// --- Getters and Setters --- 
		const std::string&      			getRawRequest() const;
		void								setInputsGet(std::string& queryString);
		void								setInputsPost(std::map<std::string, std::string> parsedData);
		void								setHeader(std::string key, std::string value);

		// ··· Request Line ··· 

		HttpMethodType          			getMethod() const;
		void								setMethod(HttpMethodType httpMethod);

		const Uri&              			getUri() const;
		void								setUri(Uri uri);

		const std::string&					getHttpVersion(void) const;
		void								setHttpVersion(const std::string& httpVersion);

		// ··· Body ··· 
		const std::string&      			getBody() const;
		int                     			getBodySize() const;

		std::string							getInput(std::string key);
		std::string							getHeader(std::string key);

	private:
		// --- Private Attributes ---
		std::string             			rawRequest_; // REVISIT : USELESS ?

		HttpRequestLine         			requestLine_;
		std::map<std::string, std::string>  headers_;
		std::map<std::string, std::string>  inputs_;
		std::string             			body_;
};

#endif