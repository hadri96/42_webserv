#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

#include "HTMLParser.hpp"

class HTTPResponse
{
    public:
    // Constructors & destructors
    HTTPResponse();
    ~HTTPResponse();

    // Methods
    std::string         getResponse();
    void                getBodyFromFile(std::string uri);
    void                getHeader(HTTPRequest *request);
	void				generateResponse(HTTPRequest *request);

    private:
    std::string     fileHeader;
    std::string     fileBody;
    std::string     fullResponse;
	HTMLParser		htmlParser;


};

#endif
