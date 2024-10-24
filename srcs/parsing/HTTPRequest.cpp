#include "../../includes/webserv.hpp"

HTTPRequest::HTTPRequest() : method("GET"), uri("example_response.html"), body("HEllo server\n\n\n") {}

HTTPRequest::~HTTPRequest() {}

void    HTTPRequest::appendRequest(std::string input)
{
    if (rawRequest.empty())
        rawRequest = input;
    else 
        rawRequest.append(input, 0, input.length());
}

std::string     HTTPRequest::getRawRequest()
{
    return (this->rawRequest);
}
