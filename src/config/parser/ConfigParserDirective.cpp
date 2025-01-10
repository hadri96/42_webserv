#include "ConfigParserDirective.hpp"

#include <iostream>
#include <sstream> // std::ostringstream

#include "Logger.hpp"

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

ConfigParserDirective::ConfigParserDirective(const std::string& directive, const std::vector<std::string> parameters) :
	directive_(directive),
	parameters_(parameters)
{
	//std::cout << "directive : " << directive << std::endl;
}

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

// =============================================================================
// Setters and Getters
// =============================================================================

std::string	ConfigParserDirective::getName(void) const
{
	return (directive_);
}

std::vector<std::string>	ConfigParserDirective::getParameters(void) const
{
	return (parameters_);
}

// =============================================================================
// Public Methods
// =============================================================================

void	ConfigParserDirective::display(void) const
{
	display(0);
}

void	ConfigParserDirective::display(int nestingLevel) const
{
	std::string indent(nestingLevel, '\t');

	std::ostringstream oss;

	oss << indent << "directive : " << directive_;
	Logger::logger()->log(LOG_DEBUG, oss);
	for (size_t i = 0; i != parameters_.size(); ++i)
	{
		oss << indent << "parameter : " << parameters_[i];
		Logger::logger()->log(LOG_DEBUG, oss);
	}
}
