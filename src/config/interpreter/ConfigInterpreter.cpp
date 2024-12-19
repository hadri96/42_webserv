#include "ConfigInterpreter.hpp"

#include <iostream>
#include <string>
#include <vector>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigInterpreter::ConfigInterpreter(void)
{
	// --- Context : root --
	const char* context1[] 		= {"root"};
	const char* blocks1[] 		= {"events","http"};
	const char* directives1[]	= {};

	// --- Context : root, http ---
	const char* context2[]		= {"root", "http"};
	const char*	blocks2[]		= {"server"};
	const char* directives2[]	= {};

	// --- Context : root, http, server --
	const char* context3[]		= {"root", "http", "server"};
	const char*	blocks3[]		= {"location"};
	const char* directives3[]	= {"server_name", "listen", "index", "error_page", "client_max_body_size", "return"};

	// --- Context : root, http, server, location --
	const char* context4[]		= {"root", "http", "server", "location"};
	const char* blocks4[]		= {"limit_except"};
	const char* directives4[]	= {"root", "autoindex", "index", "return"};

	// --- Context : root, http, server, location, limit_except --
	const char* context5[]		= {"root", "http", "server", "location", "limit_except"};
	const char* blocks5[]		= {};
	const char* directives5[]	= {"deny"};
}

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
	// --- Block ---
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
	// --- Directive ---
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

bool	ConfigInterpreter::isValidContext(std::string directive, std::vector<std::string>& context)
{
	/*

	-> set a maximum nesting allowed in the parser

	2 informations :
	-> what is valid inside a context

	// --- Context : root --
	addValidItemsToContext({root},
		// --- Allowed blocks ---
		{
			{events},
			{http}
		},
		// --- Allowed directives ---
		{}
	);

	// --- Context : root, http ---
	addValideItemsToContext{root, http}
		// --- Allowed blocks ---
		{
			{server},
		},
		// --- Allowed directives ---
		{}
	);

	// --- Context : root, http, server --
	addValidItemsToContext({root, http, server},
		// --- Allowed blocks ---
		{
			{location}
		},
		// --- Allowed directives ---
		{
			server_name,
			listen,
			index,
			error_page,
			client_max_body_size,
			return
		}
	);

	// --- Context : root, http, server, location --
	addValidItemsToContext({root, http, server, location},
		// --- Allowed blocks ---
		{
			{limit_except}
		},
		// --- Allowed directives ---
		{
			root,
			autoindex,
			index,
			return
		}
	);

	// --- Context : root, http, server, location, limit_except --
	addValidItemsToContext({root, http, server, location, limit_except},
		// --- Allowed blocks ---
		{
			{}
		},
		// --- Allowed directives ---
		{
			deny
		}
	);



	std::vector<std::vector> validBlocks


	addValidDirectivesToContext
	

	root :
		- [events]
		- [http]

	root, http :
		- [server]


	root, http, server :
		- [location]

		- server_name
		- listen
		- index
		- error_page
		- client_max_body_size
		- return

	root, http, server, location :
		- [limit_except]

		- root
		- autoindex
		- index
		- return

	root, http, server, location, limit_except :
		- deny


	-> what is mandatory (let's see if it is not better to handle with Config object directly...)

	*/
}