#include "ConfigInterpreter.hpp"

#include <iostream>
#include <string>
#include <vector>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigInterpreter::ConfigInterpreter(void)
{}

ConfigInterpreter::ConfigInterpreter(const ConfigInterpreter& other)
{
	(void) other;
}

ConfigInterpreter::~ConfigInterpreter(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigInterpreter&	ConfigInterpreter::operator=(const ConfigInterpreter& rhs)
{
	(void) rhs;
	return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

Config ConfigInterpreter::interpret(ConfigParserBlock* root)
{
	std::vector<std::string>		context;
	std::vector<ConfigParserNode*>	nodes;

	nodes = root->getNodes();
	context.push_back(root->getName());
	for (size_t i = 0; i != nodes.size(); ++i)
	{
		interpret(nodes[i], context);
	}
	Config config;
	return (config);
}

// =============================================================================
// Private Methods
// =============================================================================

void ConfigInterpreter::interpret(
	ConfigParserNode* node,
	std::vector<std::string>& context)
{
	ConfigParserBlock* block = dynamic_cast<ConfigParserBlock*>(node);
	if (block)
	{
		std::cout << "This is a block : " << node->getName() << std::endl;

		std::vector<ConfigParserNode*>	nodes;
		nodes = block->getNodes();
		context.push_back(block->getName());
		for (size_t i = 0; i != nodes.size(); ++i)
		{
			interpret(nodes[i], context);
		}
		context.pop_back();
	}
	else
	{
		std::cout << "\tThis is a directive : " << node->getName() << " ( ";

		for (size_t i = 0; i != context.size(); ++i)
		{
			std::cout << context[i] << " ";
		}
		std::cout << ")" << std::endl;

		// if directive is server and context is (root http server)
		// SERVER
		// server_name
		// listen*
		// index
		// error_page
		// client_max_body_size
		// return

		// LOCATION uri* (root http server location)
		// root*
		// autoindex
		// return
		// index

	}
}