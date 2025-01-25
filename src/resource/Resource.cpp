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

Resource::Resource(int code) :
	code_(code)
{}

Resource::Resource(int code, std::string body) :
	code_(code),
	body_(body)
{}

Resource::~Resource(void)
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

// =============================================================================
// Public Methods
// =============================================================================

int	Resource::getCode(void)
{
	return (code_);
}

const std::string&	Resource::getBody(void)
{
	return (body_);
}