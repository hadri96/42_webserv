#include "ConfigParserDirective.hpp"

#include <iostream>
#include <sstream> // std::ostringstream

#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParserDirective::ConfigParserDirective(void) :
	ConfigParserNode()
{}

ConfigParserDirective::ConfigParserDirective(const ConfigParserDirective& other) :
	ConfigParserNode(other.name_, other.parameters_)
{}

ConfigParserDirective::ConfigParserDirective(const std::string& directive, const std::vector<std::string> parameters) :
	ConfigParserNode(directive, parameters)
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
	
	name_ = rhs.name_;
	parameters_ = rhs.parameters_;

	return (*this);
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

	oss << indent << "directive : " << name_;
	Logger::logger()->log(LOG_DEBUG, oss);
	for (size_t i = 0; i != parameters_.size(); ++i)
	{
		oss << indent << "parameter : " << parameters_[i];
		Logger::logger()->log(LOG_DEBUG, oss);
	}
}
