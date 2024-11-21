#include "../../includes/webserv.hpp"

HttpRequest::HttpRequest() : method("GET"), uri("example_response.html"), body("HEllo server\n\n\n") {}

HttpRequest::~HttpRequest() {}

void    HttpRequest::appendRequest(std::string input)
{
    if (rawRequest.empty())
        rawRequest = input;
    else 
        rawRequest.append(input, 0, input.length());
}

std::string     HttpRequest::getRawRequest()
{
    return (this->rawRequest);
}
