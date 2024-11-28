#include "Route.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Route::Route(void) :
	uri_(),
	rootPath_(),
	allowedMethods_(),
	redirection_(),
	autoIndex_(false),
	defaultFile_(),
	uploadDirectory_()
{}

Route::Route(const Route& other) :
	uri_(other.uri_),
	rootPath_(other.rootPath_),
	allowedMethods_(other.allowedMethods_),
	redirection_(other.redirection_),
	autoIndex_(other.autoIndex_),
	defaultFile_(other.defaultFile_),
	uploadDirectory_(other.uploadDirectory_)
{}
Route::~Route(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Route&	Route::operator=(const Route& rhs)
{
	if (this == &rhs)
		return (*this);
	
	uri_ = rhs.uri_;
	rootPath_ = rhs.rootPath_;
	allowedMethods_ = rhs.allowedMethods_;
	redirection_ = rhs.redirection_;
	autoIndex_ = rhs.autoIndex_;
	defaultFile_ = rhs.defaultFile_;
	uploadDirectory_ = rhs.uploadDirectory_;

	return (*this);
}
