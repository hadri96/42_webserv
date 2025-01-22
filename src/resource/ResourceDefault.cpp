#include "ResourceDefault.hpp"
#include "HttpStatusCode.hpp"

#include "ToString.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ResourceDefault::ResourceDefault(void)
{}

ResourceDefault::ResourceDefault(const ResourceDefault& other) :
    Resource(other.code_)
{}

ResourceDefault::ResourceDefault(int code) :
    Resource(code)
{
    Logger::logger()->log(LOG_DEBUG, "ResourceDefault...");
    HttpStatusCode statusCode;


    body_ = 
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
            "<meta charset=\"UTF-8\">\n"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            "<title>" + toString(code) + " " + statusCode.getStatusLine(code) + "</title>\n"
        "</head>\n"
        "<body>\n"
            "<h1>" + toString(code) + " " + statusCode.getStatusLine(code) + "</h1>\n"
            "<p>" + statusCode.getMessage(code) + "</p>\n"
        "</body>\n"
    "</html>\n";
}

ResourceDefault::~ResourceDefault(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ResourceDefault&	ResourceDefault::operator=(const ResourceDefault& rhs)
{
    (void) rhs;
    return (*this);
}