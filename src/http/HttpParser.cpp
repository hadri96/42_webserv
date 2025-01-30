#include "HttpParser.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpParser::HttpParser(void)
{}

HttpParser::HttpParser(std::string httpRequestRaw) :
	httpRequestRaw_(httpRequestRaw)
{}

HttpParser::HttpParser(const HttpParser& other) :
	httpRequestRaw_(other.httpRequestRaw_)
{}

HttpParser::~HttpParser(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpParser&	HttpParser::operator=(const HttpParser& rhs)
{
	if (this == &rhs)
		return (*this);

	httpRequestRaw_ = rhs.httpRequestRaw_;
	return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

HttpRequest	HttpParser::parse(void)
{
	// HttpRequest httpRequest;

	parseHttpRequestLine();
	parseHttpBody();
    httpRequest_.log();
	return (httpRequest_);
}

// =============================================================================
// Private Methods
// =============================================================================

#include <iostream>

void	HttpParser::parseHttpRequestLine(void)
{
	std::string 		method;
	std::string 		uri;
	std::string 		version;
	std::stringstream 	ss;
	std::string 		httpRequestLine;

	ss << httpRequestRaw_;
	std::getline(ss, httpRequestLine);

	std::stringstream ss2(httpRequestLine);
    ss2 >> method >> uri >> version;

	std::string 		path;
	std::string 		queryString;
	size_t 				questionMark = uri.find('?');

	if (questionMark != std::string::npos)
	{
		path = uri.substr(0, questionMark);
		queryString = uri.substr(questionMark + 1);
	    httpRequest_.setInputsGet(queryString);
	}
	else
	{
		path = uri;
	}

	httpRequest_.setMethod(stringToHttpMethod(method));
	httpRequest_.setUri(Uri(path));
	httpRequest_.setHttpVersion(version);
}

void	HttpParser::parseHttpHeader(void)
{}

void	HttpParser::parseHttpBody(void)
{
	std::map<std::string, std::string> 		parsedData; 
	std::string								body = extractHttpBody(httpRequestRaw_);
	
    if (httpRequest_.getMethod() == POST)
    {
	    parsedData = parsePostData(body);
        httpRequest_.setInputsPost(parsedData);
    }
}

std::string 	HttpParser::extractHttpBody(const std::string& httpRequest) 
{
    std::istringstream 		ss(httpRequest);
    std::string 			line;
    std::string 			body;
    bool 					isBody = false;

    while (std::getline(ss, line)) 
	{
        if (line == "\r") 
		{
            isBody = true;
            continue;
        }
        if (isBody) 
		{
            body += line + "\n";
        }
    }
    return (body);
}

std::string		HttpParser::urlPostDecode(const std::string& encoded)
{
    std::string 	decoded;
    int 			hexVal;

    for (size_t i = 0; i < encoded.length(); i++)
    {
        if (encoded[i] == '%' && i + 2 < encoded.length())
        {
            std::istringstream hexStream(encoded.substr(i + 1, 2));
            hexStream >> std::hex >> hexVal;
            decoded += static_cast<char>(hexVal);
            i += 2;
        }
        else if (encoded[i] == '+')
        {
            decoded += ' ';
        }
        else
        {
            decoded += encoded[i];
        }
    }
    return (decoded);
}

std::map<std::string, std::string>	HttpParser::parsePostData(const std::string& postData)
{
    std::istringstream						ss(postData);
    std::string 							key;
	std::string 							value;
	std::map<std::string, std::string> 		parsedData; 

    while (std::getline(ss, key, '&'))
    {
        size_t		equalPos = key.find('=');

        if (equalPos != std::string::npos)
        {
            value = key.substr(equalPos + 1);
            key = key.substr(0, equalPos);
            parsedData[urlPostDecode(key)] = urlPostDecode(value);
        }
    }
    return (parsedData);
}
