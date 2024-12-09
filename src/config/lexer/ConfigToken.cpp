#include "ConfigToken.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigToken::ConfigToken(void) :
	type_(CT_UNKNOWN),
	value_("")
{}

ConfigToken::ConfigToken(const ConfigToken& other) :
	type_(other.type_),
	value_(other.value_)
{}

ConfigToken::ConfigToken(ConfigTokenType type, const std::string& value) :
	type_(type),
	value_(value)
{}

ConfigToken::~ConfigToken(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigToken&	ConfigToken::operator=(const ConfigToken& rhs)
{
	if (this == &rhs)
		return (*this);
	
	type_ = rhs.type_;
	value_ = rhs.value_;

	return (*this);
}

bool	ConfigToken::operator==(ConfigTokenType rhs)
{
	return (type_ == rhs);
}

bool	ConfigToken::operator!=(ConfigTokenType rhs)
{
	return (type_ != rhs);
}

// =============================================================================
// Setters and Getters
// =============================================================================

ConfigTokenType	ConfigToken::getType(void) const
{
	return (type_);
}

const std::string&	ConfigToken::getValue(void) const
{
	return (value_);
}
