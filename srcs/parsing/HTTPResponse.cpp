#include "../../includes/webserv.hpp"

HTTPResponse::HTTPResponse()
{
    this->parsed_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 400\r\n"
        "\r\n"
        "<head>\r\n"
        "<meta charset=\"UTF-8\">\r\n"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\r\n"
        "<title>Example Response</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "<h1>Welcome to the Server</h1>\r\n"
        "<p>This is a response from the server.</p>\r\n"
        "</body>";

}

HTTPResponse::~HTTPResponse()
{
    std::cout << "HTTPResponse destructor called" << std::endl;
}

std::string     HTTPResponse::getParsedResponse()
{
    return (this->parsed_response);
}


void     getRequestedFile(std::string uri)
{
    std::cout << "get requested file : " << uri  << std::endl;
}
