#include "Header.hpp"
#include "ConnectionType.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

// Using example values for testing purposes: 
Header::Header(void) :
    host_("www.example.com"),
    userAgent_("agent"),
    contentLength(0),
    contentType_("text/plain"),
    connectionType_(CLOSED),
    accept_("text/html"),
    acceptEncoding_("gzip"),
    acceptLanguage_("en-US,en,q=0.9")
{}

Header::Header(const Header& other) :
{}

Header::~Header(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Header&	Header::operator=(const Header& other)
{
	if (this == &other)
		return (*this);
    // variables = other.variables
	return (*this);
}
