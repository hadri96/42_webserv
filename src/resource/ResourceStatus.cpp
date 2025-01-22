#include "ResourceStatus.hpp"
#include "HttpStatusCode.hpp"

#include "ToString.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ResourceStatus::ResourceStatus(void)
{}

ResourceStatus::ResourceStatus(const ResourceStatus& other) :
    Resource(other.code_)
{}

ResourceStatus::ResourceStatus(int code) :
    Resource(code)
{
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

ResourceStatus::~ResourceStatus(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ResourceStatus&	ResourceStatus::operator=(const ResourceStatus& rhs)
{
    (void) rhs;
    return (*this);
}