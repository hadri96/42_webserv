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
	std::string method;
	std::string uri;
	std::string version;

	std::stringstream ss;
	std::string httpRequestLine;

	ss << httpRequestRaw_;
	std::getline(ss, httpRequestLine);

	std::stringstream ss2(httpRequestLine);
    ss2 >> method >> uri >> version;

	httpRequest_.setMethod(stringToHttpMethod(method));
	httpRequest_.setUri(Uri(uri));
	httpRequest_.setHttpVersion(version);

	// REVISIT : USE LOGGER INSTEAD
    std::cout << "Method: " << method << std::endl;
    std::cout << "URI: " << uri << std::endl;
    std::cout << "Version: " << version << std::endl;
}

void	HttpParser::parseHttpHeader(void)
{}