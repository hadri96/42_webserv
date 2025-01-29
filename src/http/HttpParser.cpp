#include "HttpParser.hpp"

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
	HttpRequest httpRequest;

	parseHttpRequestLine();

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
	}
	else
	{
		path = uri;
	}

	httpRequest_.setMethod(stringToHttpMethod(method));
	httpRequest_.setUri(Uri(path));
	httpRequest_.setInputs(queryString);
	httpRequest_.setHttpVersion(version);

	httpRequest_.log();
}

void	HttpParser::parseHttpHeader(void)
{}