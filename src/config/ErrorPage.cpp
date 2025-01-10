#include "ErrorPage.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ErrorPage::ErrorPage(void) :
	errorCode_(500),
	errorFile_(File(Path("www/errors/500.html")))
{}

ErrorPage::ErrorPage(const ErrorPage& other) :
	errorCode_(other.errorCode_),
	errorFile_(other.errorFile_)
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

	return (*this);
}

std::ostream&	operator<<(std::ostream& os, ErrorPage& object)
{
	os << "--- Error page ---" << std::endl;
	os << "  error code : " << object.getErrorCode() << std::endl;
	os << "  error file path : " << object.getErrorPath().getPath() << std::endl;

	return (os);
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

const Path&	ErrorPage::getErrorPath(void) const
{
	return (errorFile_.getPath());
}

const std::string	ErrorPage::read(void) const
{
	return (errorFile_.read());
}
