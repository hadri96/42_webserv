#include "ConfigErrorPage.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigErrorPage::ConfigErrorPage(void) :
	code_(0)
{}


ConfigErrorPage::ConfigErrorPage(const ConfigErrorPage& other) :
	code_(other.code_),
	uri_(other.uri_)
{}

ConfigErrorPage::ConfigErrorPage(int error, Uri uri) :
	code_(error),
	uri_(uri)
{}

ConfigErrorPage::~ConfigErrorPage(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigErrorPage&	ConfigErrorPage::operator=(const ConfigErrorPage& rhs)
{
	if (this == &rhs)
		return (*this);

	code_ = rhs.code_;
	uri_ = rhs.uri_;

	return (*this);
}

bool	ConfigErrorPage::operator==(int code) const
{
	return (code_ == code);
}

// =============================================================================
// Setters and Getters
// =============================================================================

int	ConfigErrorPage::getCode(void) const
{
	return (code_);
}

Uri	ConfigErrorPage::getUri(void) const
{
	return (uri_);
}

// =============================================================================
// Public Methods
// =============================================================================

void	ConfigErrorPage::display(void)
{
	std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Error page", 2);

	oss << "  error code : " << getCode();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  error uri : " << getUri().getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

	//os << "  error file path : " << object.getErrorPath().getPath() << std::endl;

}