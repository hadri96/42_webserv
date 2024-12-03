#include "ErrorPage.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ErrorPage::ErrorPage(void) :
	error_(0),
	path_()
{}
ErrorPage::ErrorPage(const ErrorPage& other) :
	error_(other.error_),
	path_(other.path_)
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

	error_ = rhs.error_;
	path_ = rhs.path_;
	return (*this);
}
