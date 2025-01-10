#include "HttpRedirection.hpp"

#include "Logger.hpp"

#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRedirection::HttpRedirection(void) :
	statusCode_(0),
	uri_()
{}

HttpRedirection::HttpRedirection(const HttpRedirection& other) :
	statusCode_(other.statusCode_),
	uri_(other.uri_)
{}

HttpRedirection::HttpRedirection(int statusCode, Uri uri) :
	statusCode_(statusCode),
	uri_(uri)
{}

HttpRedirection::~HttpRedirection(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpRedirection&	HttpRedirection::operator=(const HttpRedirection& rhs)
{
	if (this == &rhs)
		return (*this);

	statusCode_ = rhs.statusCode_;
	uri_ = rhs.uri_;

	return (*this);
}

/*std::ostream&	operator<<(std::ostream& os, HttpRedirection& object)
{
	os << "--- Redirection ---" << std::endl;


	return (os);
}*/

void	HttpRedirection::log(void)
{
    std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Redirection", 2);

    oss << "  status code : " << getStatusCode();
	Logger::logger()->log(LOG_DEBUG, oss);

    oss << "  uri : " << getUri().getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

}

// =============================================================================
// Setters and Getters
// =============================================================================

int	HttpRedirection::getStatusCode(void) const
{
	return (statusCode_);
}

const Uri&	HttpRedirection::getUri(void) const
{
	return (uri_);
}