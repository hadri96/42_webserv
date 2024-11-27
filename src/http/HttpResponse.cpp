#include "HttpResponse.hpp"
#include "ToString.hpp"
#include <iostream>
#include <fstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpResponse::HttpResponse() {}

HttpResponse::~HttpResponse() {}

// =============================================================================
// Public Methods
// =============================================================================

// Main function for generating response, should call all others in correct order
std::string     HttpResponse::generateResponse(std::string uri)
{
    getBodyFromFile(uri);
    generateStatusLine(200);
    generateHeader();
    fullResponse_.append(responseHeader_);
    fullResponse_.append(fileBody_, 0, fileBody_.length());

    std::cout << "Our HTTP Response: \n\n" << fullResponse_ << std::endl;
    return (fullResponse_);
}


// =============================================================================
// Private Methods
// =============================================================================


std::string     HttpResponse::generateStatusLine(int statusCode)
{
    if (statusCode < 400)
        return ("HTTP/1.1 " + toString(statusCode) + " OK\n\r");
    else // generate error codes here
        return ("HTTP/1.1 404 NOT FOUND\n\r"); // temporary 
}

void    HttpResponse::generateHeader()
{
    // get content type (MIME type)

    // get connection ("close" or other)

    // return responseHeader_ 
    responseHeader_ = "Content-Type: text/html\n \
                        Content-Length: " + toString(fileBody_.size()) + "\n \
                        Connection: close\n\n";  
}


// Takes the uri of the file and copies its' contents to HttpResponse->fileBody_
void     HttpResponse::getBodyFromFile(std::string uri)
{
    std::string     line;
    std::string     path = "www/static/";

    path.append(uri, 0, uri.length());

    std::ifstream        fs(path.c_str());

    if (fs.is_open())
        std::cout << "File opened: " << path << std::endl;
    while (std::getline(fs, line))
    {
        fileBody_.append(line, 0, line.length());
    }
    std::cout << "parsed file: " << fileBody_ << std::endl;
    fs.close();
}
