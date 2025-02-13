#include "ConfigParserBlock.hpp"

#include <iostream>
#include <sstream> // std::ostringstream

#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParserBlock::ConfigParserBlock(void) :
	ConfigParserNode("root")
{}

ConfigParserBlock::ConfigParserBlock(const ConfigParserBlock& other) :
	ConfigParserNode(other.name_, other.parameters_),
	nodes_(other.nodes_)
{}

ConfigParserBlock::ConfigParserBlock(const std::string& name, const std::vector<std::string> parameters) :
	ConfigParserNode(name, parameters)
{}

ConfigParserBlock::~ConfigParserBlock(void)
{
    for (size_t i = 0; i < nodes_.size(); ++i)
    {
        delete nodes_[i];
    }
    nodes_.clear();
}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigParserBlock& ConfigParserBlock::operator=(const ConfigParserBlock& rhs)
{
	if (this == &rhs)
		return (*this);
	
	name_ = rhs.name_;
	parameters_ = rhs.parameters_;
	nodes_ = rhs.nodes_;

	return (*this);
}

// =============================================================================
// Setters and Getters
// =============================================================================

const std::vector<ConfigParserNode*>& ConfigParserBlock::getNodes(void) const
{
	return (nodes_);
}

// =============================================================================
// Public Methods
// =============================================================================

void	ConfigParserBlock::addNode(ConfigParserNode* node)
{
	nodes_.push_back(node);
}

void	ConfigParserBlock::display(void) const
{
	display(0);
}


void	ConfigParserBlock::display(int nestingLevel) const
{
	std::string indent(nestingLevel, '\t');

	std::ostringstream oss;

	oss << indent << "block : " << name_;
	Logger::logger()->log(LOG_DEBUG, oss);
	for (size_t i = 0; i != parameters_.size(); ++i)
	{
		oss << indent << "parameter : " << parameters_[i];
		Logger::logger()->log(LOG_DEBUG, oss);
	}

	for (size_t i = 0; i != nodes_.size(); ++i)
	{
		if (nodes_[i])
			nodes_[i]->display(++nestingLevel);
	}
}
