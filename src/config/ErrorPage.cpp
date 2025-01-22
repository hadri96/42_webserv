#include "ErrorPage.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ErrorPage::ErrorPage(void) :
	code_(0)
{}


ErrorPage::ErrorPage(const ErrorPage& other) :
	code_(other.code_),
	uri_(other.uri_)
{}

ErrorPage::ErrorPage(int error, Uri uri) :
	code_(error),
	uri_(uri)
{}

ErrorPage::~ErrorPage(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ErrorPage&	ErrorPage::operator=(const ErrorPage& rhs)
{
	if (this == &rhs)
		return (*this);

	code_ = rhs.code_;
	uri_ = rhs.uri_;

	return (*this);
}

bool	ErrorPage::operator==(int code) const
{
	return (code_ == code);
}

// =============================================================================
// Setters and Getters
// =============================================================================

int	ErrorPage::getCode(void) const
{
	return (code_);
}

Uri	ErrorPage::getUri(void) const
{
	return (uri_);
}

// =============================================================================
// Public Methods
// =============================================================================

void	ErrorPage::display(void)
{
	std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Error page", 2);

	oss << "  error code : " << getCode();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  error uri : " << getUri().getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

	//os << "  error file path : " << object.getErrorPath().getPath() << std::endl;

}