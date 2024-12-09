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

std::string     HttpResponse::getResponseError(int errorCode)
{
    std::string     fileName = toString(errorCode) + ".html";
    std::string     errorHeaders;

    getBodyFromFile(fileName, "www/errors/");
    statusLine_ = generateStatusLine(fileName, errorCode);
    errorHeaders = generateErrorHeaders();
    fullResponse_.append(statusLine_);
    fullResponse_.append(errorHeaders);
    fullResponse_.append(body_, 0, body_.length());
    Logger::logger()->log(LOG_INFO, "\n" + fullResponse_);

    return (fullResponse_);
}

std::string     HttpResponse::getResponse(std::string uri)
{
    getBodyFromFile(uri, "www/html/");
    generateHeaderFromBody();
    fullResponse_.append(headerTemp_);
    fullResponse_.append(body_, 0, body_.length());

    return (fullResponse_);
}

// =============================================================================
// Private Methods
// =============================================================================


// Function to extract the first status text from the HTML file
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


// Function to generate the HTTP status line
std::string HttpResponse::generateStatusLine(const std::string& fileName, int errorCode) 
{
    std::string             statusText = extractStatusText(fileName);
    std::ostringstream      statusLine;

    if (errorCode == 0) 
        return "HTTP/1.1 500 Internal Server Error";

    statusLine << "HTTP/1.1 " << statusText << "\n";
    return (statusLine.str());
}

void    HttpResponse::generateHeaderFromBody()
{
    /*
        Here we should read the body_ string and deduce the correct header from it.
    */
    headerTemp_ = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: [length of the HTML content]\nConnection: close\n\n";  
}


// Function to get the current date in the required format
std::string HttpResponse::getCurrentDate()
{
    time_t      now = time(0);
    struct tm   *gmt = gmtime(&now);
    char        buffer[100];

    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", gmt);

    return (std::string(buffer));
}

// Function to generate the HTTP headers
std::string HttpResponse::generateErrorHeaders() 
{
    std::ostringstream headers;

    headers << "Date: " << getCurrentDate() << "\r\n";
    headers << "Server: Webserv\r\n";
    headers << "Content-Type: text/html; charset=UTF-8\r\n";
    headers << "Content-Length: " << body_.size() << "\r\n";
    headers << "Connection: close\r\n\n";

    return (headers.str());
}

// Takes the uri of the file and copies its' contents to HttpResponse->body_
void     HttpResponse::getBodyFromFile(std::string uri, std::string path)
{
    std::string     line;
    path.append(uri, 0, uri.length());
    std::ifstream   fs(path.c_str());

    if (fs.is_open())
        Logger::logger()->log(LOG_INFO, "File opened: " + path);
    while (std::getline(fs, line))
        body_.append(line, 0, line.length());
    fs.close();
}
