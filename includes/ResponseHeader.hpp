#ifndef HEADER_HPP
#define HEADER_HPP

#include "webserv.hpp"
#include "HTTPRequest.hpp"

class ResponseHeader
{
public:
    // Constructors & destructors

    ResponseHeader();
    ~ResponseHeader();

    // Public methods
    bool fileExists(std::string filepath);
    void createStatusCode();
    void createContentType();
    void createCacheControl();
	void createCustomHeaders();
    std::string createHeader(HTTPRequest *request);

private:
    // Private attributes
    int status_code;
	HTTPRequest *request;
    std::string contentType;
    std::string cacheControl;
    std::string responseMessage;
    std::map<std::string, std::string> customHeaders;
};

#endif

