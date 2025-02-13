#include "HttpResponse.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

#include "ResourceRedirection.hpp"

#include "HttpStatusCode.hpp"

#include "ToString.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================


HttpResponse::HttpResponse()
    : mimeType_(""), statusLine_(""), headers_(""), body_(""), fullResponse_("")
{}

HttpResponse::HttpResponse(Resource* resource)
{
    if (!resource)
    {
        
    }

    // --- Generate status line ---
    std::string         httpVersion = "HTTP/1.1";
    int code = resource->getCode();

    HttpStatusCode      statusCode;
    statusLine_ = httpVersion + " " + toString(code) + " " + statusCode.getStatusLine(code) + "\r\n";

    // --- Generate headers ---

    // REVISIT : clarify default mime type
    mimeType_ = resource->getMimeType();
	if (mimeType_.empty())
        mimeType_ = "text/html";

    body_ = resource->getBody();
	
	std::ostringstream headers;
	headers << "Server: Webserv\r\n";
    headers << "Content-Type: " <<  mimeType_ << "; charset=UTF-8\r\n";
    headers << "Content-Length: " << body_.size() << "\r\n";
    headers << "Connection: keep-alive\r\n";

    // --- Location header for redirections ---
	ResourceRedirection* resourceRedirection = dynamic_cast<ResourceRedirection*>(resource);
	if (resourceRedirection)
	{
		Logger::logger()->log(LOG_DEBUG, "HttpResponse : ResourceRedirection");
		headers << "Location: " + resourceRedirection->getUri() + "\r\n";
	}

	headers << "\r\n";
    headers_ = headers.str();
	
	composeFullResponse();

    Logger::logger()->logTitle(LOG_DEBUG, "HTTP Response (without body)");
    Logger::logger()->log(LOG_DEBUG, statusLine_ + headers_, false);

	delete resource;
}

HttpResponse::~HttpResponse()
{}

HttpResponse::HttpResponse(const HttpResponse& other)
{
    this->mimeType_ = other.mimeType_;
    this->statusLine_ = other.statusLine_;
    this->headers_ = other.headers_;
    this->body_ = other.body_;
    this->fullResponse_ = other.fullResponse_;
}

// =============================================================================
// Assignment Operators
// =============================================================================


// Copy Assignment Operator
HttpResponse& HttpResponse::operator=(const HttpResponse& other)
{
    if (this != &other)
    {
        if (other.statusLine_.empty()) 
        {
            std::cerr << "ERROR: HttpResponse being copied has an EMPTY status line!" << std::endl;
        }

        this->mimeType_ = other.mimeType_;
        this->statusLine_ = other.statusLine_;
        this->headers_ = other.headers_;
        this->body_ = other.body_;
        this->fullResponse_ = other.fullResponse_;
    }
    return *this;
}

// =============================================================================
// Public Methods
// =============================================================================

// =============================================================================
// Getters & Setters
// =============================================================================

std::string     HttpResponse::getFullResponse() const
{
    return (fullResponse_);
}

std::string     HttpResponse::getHeaders() const
{
    return (headers_);
}

// =============================================================================
// Private Methods 
// =============================================================================

void    HttpResponse::composeFullResponse()
{
    fullResponse_.append(statusLine_);
    fullResponse_.append(headers_);
    fullResponse_.append(body_, 0, body_.length());
}