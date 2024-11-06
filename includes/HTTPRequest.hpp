#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>
#include <map>
#include <sstream>

class HTTPRequest
{
    public:
        //constructors // destructors
        HTTPRequest();
        ~HTTPRequest();

		// getters
        std::string     getRawRequest();
		std::string		getMethod();
		std::string		getUri();
		std::string		getHttpVersion();
		std::string		getBody();
		std::map<std::string, std::string>	getHeaders();

		//parsing methods
        void            appendRequest(std::string input);
		void			parseRequest();
		void			parseRequestLine(std::istringstream &stream);
		void			parseBody(std::istringstream &stream);
		void			parseGetRequest(std::istringstream &stream);


    private:
        std::string     					method; // GET, POST, PUT, DELETE
        std::string     					uri; // (/index.html)
        std::string     					body;
		std::string							httpVersion;
		std::map<std::string, std::string>	headers;
		std::map<std::string, std::string>	queryParams;
        std::string     					rawRequest; // full unparsed string of the request

};


#endif
