#include "HttpResponse.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

#include "ResourceRedirection.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================


HttpResponse::HttpResponse()
{}

HttpResponse::HttpResponse(Resource* resource)
{
	Logger::logger()->log(LOG_DEBUG, "HttpResponse...");


    mimeType_ = resource->getMimeType();
	if (mimeType_.empty())
		mimeType_ = "text/html";

    body_ = resource->getBody();

    staticStatusLine();
    
	
	//generateBasicHeaders();

	std::ostringstream headers;
	headers << "Server: Webserv\r\n";
    headers << "Content-Type: " <<  mimeType_ << "; charset=UTF-8\r\n";
    headers << "Content-Length: " << body_.size() << "\r\n";
    headers << "Connection: keep-alive\r\n";

    
	ResourceRedirection* resourceRedirection = dynamic_cast<ResourceRedirection*>(resource);
	if (resourceRedirection)
	{
		Logger::logger()->log(LOG_DEBUG, "HttpResponse : ResourceRedirection");
		statusLine_ = "HTTP/1.1 301 Moved Permanently\n\r";
		headers << "Location: " + resourceRedirection->getUri() + "\r\n";
	}

	headers << "\r\n";
    headers_ = headers.str();
	std::cout << headers_ << std::endl;
	
	composeFullResponse();

	delete resource;
    //Logger::logger()->log(LOG_DEBUG, fullResponse_);
}

HttpResponse::~HttpResponse()
{}

// =============================================================================
// Public Methods
// =============================================================================


// =============================================================================
// Getters & Setters
// =============================================================================

std::string     HttpResponse::getFullResponse() const
{
    return (fullResponse_);
}

std::string     HttpResponse::getHeaders() const
{
    return (headers_);
}

// =============================================================================
// Private Methods 
// =============================================================================

// --- General Methods ---

void    HttpResponse::generateBasicHeaders()
{
    std::ostringstream headers;

    headers << "Server: Webserv\r\n";
    //headers << "Content-Type: text/html; charset=UTF-8\r\n"; // REVISIT : REPLACE BY CORRECT MIME TYPE
    headers << "Content-Type: " <<  mimeType_ << "; charset=UTF-8\r\n";
    headers << "Content-Length: " << body_.size() << "\r\n";
    headers << "Connection: keep-alive\r\n\r\n";

    headers_ = headers.str();
}

void    HttpResponse::composeFullResponse()
{
    fullResponse_.append(statusLine_);
    fullResponse_.append(headers_);
    fullResponse_.append(body_, 0, body_.length());
}

// --- Error Response Methods ---

std::string     HttpResponse::extractStatusText() const
{
    std::size_t     titleStart = body_.find("<title>");
    std::size_t     titleEnd = body_.find("</title>");

    if (titleStart != std::string::npos && titleEnd != std::string::npos) 
        return (body_.substr(titleStart + 7, titleEnd - titleStart - 7));

    return ("Unknown Error");
}

// REVISIT : NOT WORKING ANYMORE
void    HttpResponse::errorStatusLine(ConfigErrorPage& configErrorPage)
{
    std::string             statusText = extractStatusText();
    std::ostringstream      statusLine;
    int                     statusCode = configErrorPage.getCode();

    if (statusCode == 0) 
        statusLine_ = "HTTP/1.1 500 Internal Server Error";

    statusLine << "HTTP/1.1 " << statusText << "\n";
    statusLine_ = statusLine.str();
}


// --- Static Response Methods ---

void    HttpResponse::staticStatusLine()
{
    statusLine_ = "HTTP/1.1 200 OK\n\r";
}
