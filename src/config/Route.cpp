#include "Route.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Route::Route(void) :
	allowedMethods_(),
	httpRedirection_(),
	routePath_(),
	autoIndex_(false),
	defaultFile_(),
	uploadDirectory_()
{}

Route::Route(const Route& other) :
	allowedMethods_(other.allowedMethods_),
	httpRedirection_(other.httpRedirection_),
	routePath_(other.routePath_),
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
	
	allowedMethods_ = rhs.allowedMethods_;
	httpRedirection_ = rhs.httpRedirection_;
	routePath_ = rhs.routePath_;
	autoIndex_ = rhs.autoIndex_;
	defaultFile_ = rhs.defaultFile_;
	uploadDirectory_ = rhs.uploadDirectory_;

	return (*this);
}