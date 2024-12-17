#include "ConfigParserBlock.hpp"

#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParserBlock::ConfigParserBlock(void) :
	block_("root")
{}

ConfigParserBlock::ConfigParserBlock(const ConfigParserBlock& other) :
	block_(other.block_),
	parameters_(other.parameters_),
	nodes_(other.nodes_)
{}

ConfigParserBlock::ConfigParserBlock(const std::string& block, const std::vector<std::string> parameters) :
	block_(block),
	parameters_(parameters)
{
	/*std::cout << "Block created : " << block_ << std::endl;
	for (size_t i = 0; i != parameters_.size(); ++i)
	{
		std::cout << "Parameter : " << parameters_[i] << " ";
	}
	std::cout << std::endl;*/
}

ConfigParserBlock::~ConfigParserBlock(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigParserBlock& ConfigParserBlock::operator=(const ConfigParserBlock& rhs)
{
	if (this == &rhs)
		return (*this);
	
	block_ = rhs.block_;
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

std::string	ConfigParserBlock::getName(void) const
{
	return (block_);
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

	std::cout << indent << "block : " << block_ << std::endl;
	for (size_t i = 0; i != parameters_.size(); ++i)
	{
		std::cout << indent << "parameter : " << parameters_[i] << std::endl;
	}

	for (size_t i = 0; i != nodes_.size(); ++i)
	{
		if (nodes_[i])
			nodes_[i]->display(++nestingLevel);
	}
}
