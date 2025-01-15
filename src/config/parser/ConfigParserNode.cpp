#include "ConfigParserNode.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParserNode::ConfigParserNode(void) :
	name_("")
{}

ConfigParserNode::ConfigParserNode(const std::string& name) :
	name_(name)
{}

ConfigParserNode::ConfigParserNode(const std::string& name, const std::vector<std::string>& parameters) : 
	name_(name), parameters_(parameters)
{}

ConfigParserNode::~ConfigParserNode(void)
{}

std::string	ConfigParserNode::getName(void) const
{
	return (name_);
}

std::vector<std::string>	ConfigParserNode::getParameters(void) const
{
	return (parameters_);
}