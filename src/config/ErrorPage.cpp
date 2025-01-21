#include "ErrorPage.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ErrorPage::ErrorPage(void) :
	errorCode_(500),
	errorFile_(File(Path("www/errors/500.html")))
{}

ErrorPage::ErrorPage(int errorCode) :
	errorCode_(errorCode),
	errorFile_(File(errorCode))
{}

ErrorPage::ErrorPage(const ErrorPage& other) :
	errorCode_(other.errorCode_),
	errorFile_(other.errorFile_),
	uri_(other.uri_)
{}

ErrorPage::ErrorPage(int error, Uri uri) :
	errorCode_(error),
	uri_(uri)
{}

ErrorPage::ErrorPage(int error, const Path& path) :
	errorCode_(error),
	errorFile_(File(path))
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

	errorCode_ = rhs.errorCode_;
	errorFile_ = rhs.errorFile_;
	uri_ = rhs.uri_;

	return (*this);
}

bool	ErrorPage::operator==(int code) const
{
	return (errorCode_ == code);
}

// =============================================================================
// Setters and Getters
// =============================================================================

int	ErrorPage::getErrorCode(void) const
{
	return (errorCode_);
}

const File&	ErrorPage::getErrorFile(void) const
{
	return (errorFile_);
}

const Path	ErrorPage::getErrorPath(void) const
{
	return (errorFile_.getPath());
}

Uri	ErrorPage::getErrorUri(void) const
{
	return (uri_);
}

const std::string	ErrorPage::read(void) const
{
	return (errorFile_.read());
}

// =============================================================================
// Public Methods
// =============================================================================

void	ErrorPage::display(void)
{
	std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Error page", 2);

	oss << "  error code : " << getErrorCode();
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  error uri : " << getErrorUri().getUri();
	Logger::logger()->log(LOG_DEBUG, oss);

	//os << "  error file path : " << object.getErrorPath().getPath() << std::endl;

}