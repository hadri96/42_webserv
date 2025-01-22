#include "ConfigRedirection.hpp"

#include "Logger.hpp"

#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigRedirection::ConfigRedirection(void) :
	statusCode_(0),
	uri_()
{}

ConfigRedirection::ConfigRedirection(const ConfigRedirection& other) :
	statusCode_(other.statusCode_),
	uri_(other.uri_)
{}

ConfigRedirection::ConfigRedirection(int statusCode, Uri uri) :
	statusCode_(statusCode),
	uri_(uri)
{}

ConfigRedirection::~ConfigRedirection(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigRedirection&	ConfigRedirection::operator=(const ConfigRedirection& rhs)
{
	if (this == &rhs)
		return (*this);

	statusCode_ = rhs.statusCode_;
	uri_ = rhs.uri_;

	return (*this);
}

/*std::ostream&	operator<<(std::ostream& os, ConfigRedirection& object)
{
	os << "--- Redirection ---" << std::endl;


	return (os);
}*/

void	ConfigRedirection::log(void)
{
    std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Redirection", 2);

    oss << "  status code : " << getStatusCode();
	Logger::logger()->log(LOG_DEBUG, oss);

    oss << "  uri : " << getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

}

// =============================================================================
// Setters and Getters
// =============================================================================

int	ConfigRedirection::getStatusCode(void) const
{
	return (statusCode_);
}

const Uri&	ConfigRedirection::getUri(void) const
{
	return (uri_);
}