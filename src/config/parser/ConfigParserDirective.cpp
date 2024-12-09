#include "ConfigParserDirective.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParserDirective::ConfigParserDirective(void) :
	directive_("")
{}

ConfigParserDirective::ConfigParserDirective(const ConfigParserDirective& other) :
	directive_(other.directive_),
	parameters_(other.parameters_)
{}

ConfigParserDirective::ConfigParserDirective(const std::string& directive, const std::vector<std::string>& parameters) :
	directive_(directive),
	parameters_(parameters)
{}

ConfigParserDirective::~ConfigParserDirective(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigParserDirective& ConfigParserDirective::operator=(const ConfigParserDirective& rhs)
{
	if (this == &rhs)
		return (*this);
	
	directive_ = rhs.directive_;
	parameters_ = rhs.parameters_;

	return (*this);
}
