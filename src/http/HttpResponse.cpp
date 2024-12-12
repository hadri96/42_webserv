#include "HttpResponse.hpp"
#include "Logger.hpp"
#include "ToString.hpp"
#include "File.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================


HttpResponse::HttpResponse() {}

HttpResponse::~HttpResponse() {}


// =============================================================================
// Public Methods
// =============================================================================

// So far this function only handles static GET requests and Error pages
std::string     HttpResponse::generateStaticResponse(File& file)
{    
    body_ = file.read();
    Logger::logger()->log(LOG_DEBUG, body_);
    staticStatusLine();
    generateBasicHeaders();
    composeFullResponse();

    return (fullResponse_);
}

std::string     HttpResponse::generateStaticResponse(ErrorPage& errorPage)
{
    body_ = errorPage.read();
    Logger::logger()->log(LOG_DEBUG, body_);
    errorStatusLine(errorPage);
    generateBasicHeaders();
    composeFullResponse();

    return (fullResponse_);
}

// =============================================================================
// Private Methods 
// =============================================================================

// --- General Methods ---


std::string     HttpResponse::getCurrentTime() const
{
	std::time_t currentTime;
	std::tm* 	localTime;
	char		timeBuffer[20];

	currentTime = std::time(0);
	localTime = std::localtime(&currentTime);
	std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
	return (std::string(timeBuffer));
}

void    HttpResponse::generateBasicHeaders()
{
    std::ostringstream headers;

    headers << "Date: " << getCurrentTime() << "\r\n";
    headers << "Server: Webserv\r\n";
    headers << "Content-Type: text/html; charset=UTF-8\r\n";
    headers << "Content-Length: " << body_.size() << "\r\n";
    headers << "Connection: keep-alive\r\n\r\n";

    headers_ = headers.str();
}

void    HttpResponse::composeFullResponse()
{
    fullResponse_.append(statusLine_);
    fullResponse_.append(headers_);
    fullResponse_.append(body_, 0, body_.length());
    Logger::logger()->log(LOG_DEBUG, "Full Response\n" + fullResponse_);
}

// --- Error Response Methods ---

std::string     HttpResponse::extractStatusText() const
{
    std::size_t     titleStart = body_.find("<title>");
    std::size_t     titleEnd = body_.find("</title>");

    if (titleStart != std::string::npos && titleEnd != std::string::npos) 
        return body_.substr(titleStart + 7, titleEnd - titleStart - 7);

    return ("Unknown Error");
}

void    HttpResponse::errorStatusLine(ErrorPage& errorPage)
{
    std::string             statusText = extractStatusText();
    std::ostringstream      statusLine;
    int                     statusCode = errorPage.getErrorCode();

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
