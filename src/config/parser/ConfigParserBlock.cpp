#include "ConfigParserBlock.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParserBlock::ConfigParserBlock(void) :
	block_("")
{}

ConfigParserBlock::ConfigParserBlock(const ConfigParserBlock& other) :
	block_(other.block_),
	parameters_(other.parameters_),
	nodes_(other.nodes_)
{}

ConfigParserBlock::ConfigParserBlock(const std::string& block, const std::vector<std::string>& parameters) :
	block_(block),
	parameters_(parameters)
{}

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
// Public Methods
// =============================================================================

void	ConfigParserBlock::addNode(ConfigParserNode& node)
{
	nodes_.push_back(&node);
}
