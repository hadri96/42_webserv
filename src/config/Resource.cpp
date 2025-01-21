#include "Resource.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Resource::Resource(void) :
	code_(0)
{}

Resource::Resource(const Resource& other) :
	code_(other.code_),
	body_(other.body_)
{}

Resource::Resource(int code, std::string body) :
	code_(code),
	body_(body)
{}

Resource::Resource(int code, File file) :
	code_(code),
	body_(file.read())
{}

// =============================================================================
// Operators Overload
// =============================================================================

Resource&	Resource::operator=(const Resource& rhs)
{
	if (this == &rhs)
		return (*this);

	code_ = rhs.code_;
	body_ = rhs.body_;

	return (*this);
}
