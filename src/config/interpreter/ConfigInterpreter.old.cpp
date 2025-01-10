#include "ConfigInterpreter.hpp"
#include "ConfigInterpreterContext.hpp"

#include "ToVector.hpp"
#include "ToInt.hpp"

#include <iostream>
#include <string>
#include <vector>

// =============================================================================
// Constructors and Destructor
// =============================================================================

/*
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
*/

ConfigInterpreter::ConfigInterpreter(void)
{
	std::vector<ConfigInterpreterContext> rules;

	/*
	 Defines the allowed blocks and directives for a given context.
	 */
	// --- Context : root --
	const char* context1[] 		= {"root"};
	const char* blocks1[] 		= {"events","http"};
	const char* directives1[]	= {""};
	void (ConfigInterpreter::*handlers1[])(ConfigParserNode* node) = {0};
	
	// --- Context : root, http ---
	const char* context2[]		= {"root", "http"};
	const char*	blocks2[]		= {"server"};
	const char* directives2[]	= {""};
	void (ConfigInterpreter::*handlers2[])(ConfigParserNode* node) = {0};

	// --- Context : root, http, server --
	const char* context3[]		= {"root", "http", "server"};
	const char*	blocks3[]		= {"location"};
	
	const char* directives3[]	= {"server_name", "listen", "index", "error_page", "client_max_body_size", "return"};
	void (ConfigInterpreter::*handlers3[])(ConfigParserNode* node) = {
		&ConfigInterpreter::handleServerName,
		&ConfigInterpreter::handleServerListen,
		&ConfigInterpreter::handleServerIndex,
		&ConfigInterpreter::handleServerErrorPage,
		&ConfigInterpreter::handleServerClientMaxBodySize,
		&ConfigInterpreter::handleServerReturn
	};

	// --- Context : root, http, server, location --
	const char* context4[]		= {"root", "http", "server", "location"};
	const char* blocks4[]		= {"limit_except"};
	const char* directives4[]	= {"root", "autoindex", "index", "return"};
	void (ConfigInterpreter::*handlers4[])(ConfigParserNode* node) = {
		&ConfigInterpreter::handleRouteRoot,
		&ConfigInterpreter::handleRouteAutoIndex,
		&ConfigInterpreter::handleRouteIndex,
		&ConfigInterpreter::handleRouteReturn
	};

	// --- Context : root, http, server, location, limit_except --
	const char* context5[]		= {"root", "http", "server", "location", "limit_except"};
	const char* blocks5[]		= {""};
	const char* directives5[]	= {"deny"};
	void (ConfigInterpreter::*handlers5[])(ConfigParserNode* node) = {
		ConfigInterpreter::&handleMethodAllowed
	};

	/*addValidItemsToContext(toVector(context1), toVector(blocks1), toVector(directives1));
	addValidItemsToContext(toVector(context2), toVector(blocks2), toVector(directives2));
	addValidItemsToContext(toVector(context3), toVector(blocks3), toVector(directives3));
	addValidItemsToContext(toVector(context4), toVector(blocks4), toVector(directives4));
	addValidItemsToContext(toVector(context5), toVector(blocks5), toVector(directives5));*/

	rules.push_back(ConfigInterpreterContext(context1, blocks1, directives1, handlers1));
	rules.push_back(ConfigInterpreterContext(context2, blocks2, directives2, handlers2));
	rules.push_back(ConfigInterpreterContext(context3, blocks3, directives3, handlers3));
	rules.push_back(ConfigInterpreterContext(context4, blocks4, directives4, handlers4));
	rules.push_back(ConfigInterpreterContext(context5, blocks5, directives5, handlers5));

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

void	ConfigInterpreter::interpret(
	ConfigParserNode* node,
	std::vector<std::string>& context)
{
	ConfigParserBlock* block = dynamic_cast<ConfigParserBlock*>(node);
	// --- Block ---
	if (block)
	{
		std::cout << "Block : `" << node->getName() << "` in context : `" << getDisplayableContext(context) << "`" << std::endl;
		if (!isBlockValidInContext(node->getName(), context))
			throw std::runtime_error("The block `" + node->getName() + "` is invalid in context `" + getDisplayableContext(context) + "`");

		// --- Recursively treating the content of the block ---
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
		std::cout << "\tDirective : `" << node->getName() << "` in context : `" << getDisplayableContext(context) << "`" << std::endl;
		if (!isDirectiveValidInContext(node->getName(), context))
			throw std::runtime_error("The directive `" + node->getName() + "` is invalid in context `" + getDisplayableContext(context) + "`");
	}
}

void	ConfigInterpreter::interpretBlock(ConfigParserNode* node, std::string block, std::vector<std::string>& context)
{
	if (block == "server")
		servers_.push_back(new Config);			// Add a new empty server config
	else if (block == "location")
		servers_.back().setRoute(new Route);	// Add a new empty route config to the current server config 
}

void	ConfigInterpreter::interpretDirective(ConfigParserNode* node, std::string directive, std::vector<std::string>& context)
{
	const char* correspondingContext[] = {"root", "http", "server"};
	if (toVector(correspondingContext) == context)
	{
		const char* directives[]	= {"server_name", "listen", "index", "error_page", "client_max_body_size", "return"};
	}
	
	const char* correspondingContext[] = {"root", "http", "server", "location"};
	if (toVector(correspondingContext) == context)
	{
		const char* directives[]	= {"root", "autoindex", "index", "return"}
	}

	const char* correspondingContext[] = {"root", "http", "server", "location", "limit_except"};
	if (toVector(correspondingContext) == context)
	{
		const char* directives[]	= {"deny"};
	}


	// --- Context : root, http, server ---
	// - server_name
	// - listen
	// - index
	// - error_page
	// - client_max_body_size
	// - return

	std::vector<std::string> parameters;
	parameters = node->getParameters();

	// handleServerName
	if (directive == "server_name")
	{

		if (parameters.size() != 1)
			std::runtime_error("interpreter : server_name : wrong number of parameters");
		servers_.back()->setServerName(parameters[0]);
	}
	// handleServerListen
	else if (directive == "listen")
	{
		if (parameters.size() != 1)
			throw std::runtime_error("interpreter : listen : wrong number of parameters");

		size_t position = parameters[0].find(':');
		if (position == std::string::npos)
			throw std::runtime_error("interpreter : listen : invalid format, expected 'host:port'");

		std::string host = parameters[0].substr(0, position);
		std::string port = parameters[0].substr(position + 1);

		servers_.back()->setHost(host);
		servers_.back()->setPort(toInt(port));
	}
	// handleServerIndex
	else if (directive == "index")
	{

	}
	// handleServerErrorPage
	else if (directive == "error_page")
	{

	}
	// handleServerClientMaxBodySize
	else if (directive == "client_max_body_size")
	{

	}
	// handleServerReturn
	else if (directive == "return")
	{

	}
	
	// --- Context : root, http, server, location ---
	// - root
	// - autoindex
	// - index
	// - return

}
// --- Handlers ---

void	ConfigInterpreter::handleServerName(ConfigParserNode* node)
{
	// Implementation here
}
void	ConfigInterpreter::handleServerListen(ConfigParserNode* node)
{
	// Implementation here
}

void	ConfigInterpreter::handleServerIndex(ConfigParserNode* node)
{
	// Implementation here
}

void	ConfigInterpreter::handleServerErrorPage(ConfigParserNode* node)
{
	// Implementation here
}

void	ConfigInterpreter::handleServerClientMaxBodySize(ConfigParserNode* node)
{
	// Implementation here
}

void	ConfigInterpreter::handleServerReturn(ConfigParserNode* node)
{
	// Implementation here
}

void	ConfigInterpreter::handleRouteRoot(ConfigParserNode* node)
{

}

void	ConfigInterpreter::handleRouteAutoIndex(ConfigParserNode* node)
{

}

void	ConfigInterpreter::handleRouteIndex(ConfigParserNode* node)
{
	
}

void	ConfigInterpreter::handleRouteReturn(ConfigParserNode* node)
{
	
}

void	ConfigInterpreter::handleMethodAllowed(ConfigParserNode* node)
{
	
}

// --- Checkers ---

bool	ConfigInterpreter::isBlockValidInContext(std::string block, std::vector<std::string>& context)
{
	std::vector<std::string>	validBlocks;

	validBlocks = validBlocks_[context];
	for (size_t i = 0; i != validBlocks.size(); ++i)
	{
		if (validBlocks[i] == block)
			return (true);
	}
	return (false);
}
bool	ConfigInterpreter::isDirectiveValidInContext(std::string directive, std::vector<std::string>& context)
{
	std::vector<std::string>	validDirectives;

	validDirectives = validDirectives_[context];
	for (size_t i = 0; i != validDirectives.size(); ++i)
	{
		if (validDirectives[i] == directive)
			return (true);
	}
	return (false);
}

void	ConfigInterpreter::addValidItemsToContext(
			std::vector<std::string> context,
			std::vector<std::string> validBlocks,
			std::vector<std::string> validDirectives
		)
{
	validBlocks_[context] = validBlocks;
	validDirectives_[context] = validDirectives;	
}

std::string	ConfigInterpreter::getDisplayableContext(std::vector<std::string>& context)
{
	std::string displayableContext;
	for (size_t i = 0; i != context.size(); ++i)
	{
		displayableContext.append(context[i]);
		if (i != context.size() - 1)
			displayableContext.append("->");
	}
	return (displayableContext);
}