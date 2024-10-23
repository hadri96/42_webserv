#include "../../includes/webserv.hpp"

HTTPResponse::HTTPResponse() {}

HTTPResponse::~HTTPResponse()
{
    std::cout << "HTTPResponse destructor called" << std::endl;
}


std::string     HTTPResponse::getResponse(std::string uri)
{
    getBodyFromFile(uri);
    getHeaderFromBody();
    fullResponse.append(fileHeader);
    fullResponse.append(fileBody, 0, fileBody.length());

    return (this->fullResponse);
}


void    HTTPResponse::getHeaderFromBody()
{
    /*
        Here we should read the fileBody string and deduce the correct header from it.
    */
    fileHeader = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: [length of the HTML content]\nConnection: close\n\n";  
}


// Takes the uri of the file and copies its' contents to HTTPResponse->fileBody
void     HTTPResponse::getBodyFromFile(std::string uri)
{
    std::string     line;
    std::string     path = "html/";
    path.append(uri, 0, uri.length()); // problem with the uri

    std::ifstream        fs(path.c_str());

    if (fs.is_open())
        std::cout << "File opened: " << path << std::endl;
    while (std::getline(fs, line))
    {
        fileBody.append(line, 0, line.length());
    }
    std::cout << "parsed file: " << fileBody << std::endl;
    fs.close();
}
