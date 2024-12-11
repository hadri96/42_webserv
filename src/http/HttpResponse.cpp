#include "HttpResponse.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

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
std::string     HttpResponse::getResponse(int statusCode, std::string uri)
{
    Logger::logger()->log(LOG_INFO, "getResponse");
    if (statusCode >= 400)
    {
        std::string     fileName = toString(statusCode) + ".html";
        
        getBodyFromFile(fileName, "www/.errors/");
        ErrorStatusLine(fileName, statusCode);
    }
    else if (statusCode == 200 && uri != "")
    {
        getBodyFromFile(uri, "www/html/");
        staticStatusLine();
    }
    generateBasicHeaders();
    composeFullResponse();

    return (fullResponse_);
}

// =============================================================================
// Private Methods 
// =============================================================================

// --- General Methods ---

void     HttpResponse::getBodyFromFile(std::string uri, std::string path)
{
    std::string         line;
    
    path.append(uri, 0, uri.length());
    
    std::ifstream       fileStream(path.c_str());

    if (fileStream.is_open())
        Logger::logger()->log(LOG_INFO, "File opened: " + path);
    while (std::getline(fileStream, line))
        body_.append(line, 0, line.length());
    fileStream.close();
}

std::string HttpResponse::getCurrentDate()
{
    time_t      now = time(0);
    struct tm   *gmt = gmtime(&now);
    char        buffer[100];

    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", gmt);

    return (std::string(buffer));
}

void    HttpResponse::generateBasicHeaders() 
{
    std::ostringstream headers;

    headers << "Date: " << getCurrentDate() << "\r\n";
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
    Logger::logger()->log(LOG_INFO, "Full Response\n" + fullResponse_);
}

// --- Error Response Methods ---

std::string     HttpResponse::extractStatusText(const std::string& fileName) 
{
    std::string         line;
    std::string         path = "www/errors/";

    path.append(fileName, 0, fileName.length());

    std::ifstream        htmlFile(path.c_str());

    if (!htmlFile.is_open()) 
        return ("Unknown Error");
    while (std::getline(htmlFile, line)) 
    {
        std::size_t     titleStart = line.find("<title>");
        std::size_t     titleEnd = line.find("</title>");

        if (titleStart != std::string::npos && titleEnd != std::string::npos) 
            return (line.substr(titleStart + 7, titleEnd - titleStart - 7));
    }
    htmlFile.close();
    return ("Unknown Error");
}

void    HttpResponse::ErrorStatusLine(const std::string& fileName, int statusCode) 
{
    std::string             statusText = extractStatusText(fileName);
    std::ostringstream      statusLine;

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
