#include "ErrorPage.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ErrorPage::ErrorPage(void) :
	errorCode_(0),
	errorPage_()
{}
ErrorPage::ErrorPage(const ErrorPage& other) :
	errorCode_(other.errorCode_),
	errorPage_(other.errorPage_)
{}

ErrorPage::ErrorPage(int error, const Path& path) :
	errorCode_(error),
	errorPage_(path)
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
	errorPage_ = rhs.errorPage_;

	return (*this);
}

// =============================================================================
// Setters and Getters
// =============================================================================

int	ErrorPage::getErrorCode(void) const
{
	return (errorCode_);
}

const Path&	ErrorPage::getErrorPage(void) const
{
	return (errorPage_);
}
