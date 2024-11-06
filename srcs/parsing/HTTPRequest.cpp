#include "webserv.hpp"

HTTPRequest::HTTPRequest() : method("GET"), uri("example_response.html"), body("HEllo server\n\n\n") {}

HTTPRequest::~HTTPRequest() {}

void    HTTPRequest::appendRequest(std::string input)
{
    if (rawRequest.empty())
        rawRequest = input;
    else
        rawRequest.append(input, 0, input.length());
}

std::string	HTTPRequest::getRawRequest() { return (rawRequest); }

std::string	HTTPRequest::getMethod() { return (method); }

std::string	HTTPRequest::getUri(){ return (uri); }

std::string	HTTPRequest::getHttpVersion(){ return (httpVersion); }

std::map<std::string, std::string>	HTTPRequest::getHeaders() { return (headers); }

std::string	HTTPRequest::getBody() { return (body); }

void	HTTPRequest::parseRequestLine(std::istringstream &stream)
{
	std::string requestLine;

	if (std::getline(stream, requestLine))
	{
		std::istringstream lineStream(requestLine);
		lineStream >> this->method;
		if (lineStream.peek() == '/')
			return ;
		lineStream >> this->uri >> this->httpVersion;
		if (this->uri.find('?') != std::string::npos)
		{
			std::string queryString = this->uri.substr(this->uri.find('?') + 1);
			this->uri = this->uri.substr(0, this->uri.find('?')); // Remove query string from path

			// Parse query parameters
			std::istringstream queryStream(queryString);
			std::string param;
			while (std::getline(queryStream, param, '&'))
			{
				size_t pos = param.find('=');
				if (pos != std::string::npos)
				{
					std::string key = param.substr(0, pos);
					std::string value = param.substr(pos + 1);
					queryParams[key] = value; // Store in map
				}
			}
		}
	}
}

void	HTTPRequest::parseGetRequest(std::istringstream &stream)
{
	if (this->uri.find(".css") != std::string::npos)
	{
		std::cout << "CSS URI: " << this->uri << std::endl;
	}
	parseBody(stream);
}

void	HTTPRequest::parseBody(std::istringstream &stream)
{
	std::string line;
	while (std::getline(stream, line) && !line.empty())
	{
		size_t colon = line.find(':');
		if (colon != std::string::npos)
		{
			std::string key = line.substr(0, colon);
			std::string value = line.substr(colon + 1);
			// Trim leading whitespace from the value
			if (!value.empty() && value[0] == ' ')
			{
				value.erase(0, 1);
			}
			headers[key] = value;
		}
	}
}

void	HTTPRequest::parseRequest()
{
	std::istringstream stream(this->rawRequest);
	parseRequestLine(stream);
	if (this->method == "GET")
		parseGetRequest(stream);
}
