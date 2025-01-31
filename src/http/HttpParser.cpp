#include "HttpParser.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

#include <sstream>
#include <iostream>

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
    parseHttpHeader();
	parseHttpBody();
    httpRequest_.log();
	return (httpRequest_);
}

// =============================================================================
// Private Methods
// =============================================================================

// ·············································································
// Main Parsers
// ·············································································


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


void HttpParser::parseHttpHeader(void)
{
    std::istringstream      stream(httpRequestRaw_);
    std::string             line;

    if (!std::getline(stream, line) || line.empty()) 
    {
        return;
    }
    
    while (std::getline(stream, line) && !line.empty()) 
    {
        if (line == "\r") 
        {
            break;
        }

        std::size_t         colonPos = line.find(':');

        if (colonPos != std::string::npos) 
        {
            std::string     key = line.substr(0, colonPos);
            std::string     value = line.substr(colonPos + 1);

            key = trimString(key);
            value = trimString(value);

            httpRequest_.setHeader(key, value);
        }
    }
}

void HttpParser::parseHttpBody(void)
{
    std::string         body = extractHttpBody(httpRequestRaw_);
    std::string         contentType = httpRequest_.getHeader("Content-Type");

    if (httpRequest_.getMethod() == POST)
    {
        if (contentType.find("multipart/form-data") != std::string::npos)
        {
            httpRequest_.setMultipartData(parseMultipartData(body, contentType));
        }
        else
        {
            std::map<std::string, std::string> parsedData = parsePostData(body);
            httpRequest_.setInputsPost(parsedData);
        }
    }
}


// ·············································································
// Parsing Utils
// ·············································································


std::string HttpParser::trimString(const std::string& str)
{
    std::size_t             first = str.find_first_not_of(" \t");
    std::size_t             last = str.find_last_not_of(" \t\r");
    
    if (first == std::string::npos || last == std::string::npos) 
    {
        return "";
    }
    
    return (str.substr(first, last - first + 1));
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

// ·············································································
// Multipart data Parsing
// ·············································································


std::map<std::string, std::string>  HttpParser::parseMultipartData(const std::string& body, const std::string& contentType)
{
    std::map<std::string, std::string>  parsedData;
    std::string                         boundary;
    size_t                              boundaryPos = contentType.find("boundary=");

    if (boundaryPos == std::string::npos)
        return parsedData;

    boundary = "--" + contentType.substr(boundaryPos + 9); // Skip "boundary="

    std::vector<std::string>            parts;
    size_t                              pos = 0;
    size_t                              nextPos;

    while ((nextPos = body.find(boundary, pos)) != std::string::npos)
    {
        std::string part = body.substr(pos, nextPos - pos);
        pos = nextPos + boundary.length();
        if (!part.empty())
            parts.push_back(part);
    }

    for (size_t i = 0; i < parts.size(); i++)
    {
        std::istringstream      stream(parts[i]);
        std::string             line;
        std::string             fieldName;
        std::string             fileName;
        std::string             content;
        bool                    isFile = false;

        while (std::getline(stream, line) && !line.empty())
        {
            if (line.find("Content-Disposition:") != std::string::npos)
            {
                size_t          namePos = line.find("name=\"");
                if (namePos != std::string::npos)
                {
                    size_t      nameEnd = line.find("\"", namePos + 6);
                    fieldName = line.substr(namePos + 6, nameEnd - (namePos + 6));
                }

                size_t          filePos = line.find("filename=\"");
                if (filePos != std::string::npos)
                {
                    size_t      fileEnd = line.find("\"", filePos + 10);
                    fileName = line.substr(filePos + 10, fileEnd - (filePos + 10));
                    isFile = true;
                }
            }
        }

        while (std::getline(stream, line))
            content += line + "\n";

        if (!content.empty() && content[content.length() - 1] == '\n')
            content.erase(content.length() - 1);

        if (isFile)
        {
            parsedData["file_name"] = fileName;
            parsedData["file_content"] = content;
        }
        else
        {
            parsedData[fieldName] = content;
        }
    }

    return (parsedData);
}
