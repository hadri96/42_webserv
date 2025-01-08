#include "ConfigInterpreter.hpp"
#include "ConfigInterpreterRule.hpp"

#include "ToVector.hpp"
#include "ToInt.hpp"
#include "Join.hpp"
#include "AllOf.hpp"
#include "IsIp.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "Colors.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================


ConfigInterpreter::ConfigInterpreter(void) :
	currentConfig_(-1)
{
	/*
	 Defines the allowed blocks and directives for a given context.
	 */
	// --- Context : root ---
	const char* context1[] 		= {"root", 0};
	const char* blocks1[] 		= {"events","http", 0};
	const char* directives1[]	= {0};

	// --- Context : root, http ---
	const char* context2[]		= {"root", "http", 0};
	const char*	blocks2[]		= {"server", 0};
	const char* directives2[]	= {0};

	// --- Context : root, http, server ---
	const char* context3[]		= {"root", "http", "server", 0};
	const char*	blocks3[]		= {"location", 0};
	const char* directives3[]	= {"server_name", "listen", "index", "error_page", "client_max_body_size", "return", 0};

	// --- Context : root, http, server, location ---
	const char* context4[]		= {"root", "http", "server", "location", 0};
	const char* blocks4[]		= {"limit_except", 0};
	const char* directives4[]	= {"root", "autoindex", "index", "return", 0};
	
	// --- Context : root, http, server, location, limit_except ---
	const char* context5[]		= {"root", "http", "server", "location", "limit_except", 0};
	const char* blocks5[]		= {0};
	const char* directives5[]	= {"deny", 0};

	//void (ConfigInterpreter::*handlers5[])(ConfigParserNode*) = {0};

	addRule(ConfigInterpreterRule(context1, blocks1, directives1));
	addRule(ConfigInterpreterRule(context2, blocks2, directives2));
	addRule(ConfigInterpreterRule(context3, blocks3, directives3));
	addRule(ConfigInterpreterRule(context4, blocks4, directives4));
	addRule(ConfigInterpreterRule(context5, blocks5, directives5));

	for (size_t i = 0; i != rules_.size(); ++i)
	{
		std::cout << rules_[i] << std::endl;
	}
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

void	ConfigInterpreter::addRule(const ConfigInterpreterRule& rule)
{
	rules_.push_back(rule);
}

Config	ConfigInterpreter::interpret(ConfigParserBlock* root)
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
		std::cout << "Block : `" << node->getName() << "` in context : `" << join(context, "->") << "`" << std::endl;
		if (!isBlockValidInContext(node->getName(), context))
			throw std::runtime_error("The block `" + node->getName() + "` is invalid in context `" + join(context, "->") + "`");

		if (node->getName() == "server")
		{
			Config newConfig;
			configs_.push_back(newConfig);
		}
		/*else if (node->getName() == "location")
		{
			if (node->getParameters().size() != 1)
				throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

			Route newRoute;
			Uri newUri;
			configs_.back().addRoute(newRoute);

			newUri.setUri(node->getParameters[0]);
			configs_.back().getRoutes().back().setUri(newUri);
		}*/

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
		std::cout << "\tDirective : `" << node->getName() << "` in context : `" << join(context, "->") << "`" << std::endl;
		if (!isDirectiveValidInContext(node->getName(), context))
			throw std::runtime_error("The directive `" + node->getName() + "` is invalid in context `" + join(context, "->") + "`");

		if (node->getName() == "server_name")
			handleServerName(node);
		else if (node->getName() == "listen")
			handleListen(node);
		else if (node->getName() == "index")
			handleIndex(node);
		else if (node->getName() == "error_page")
			handleErrorPage(node);
		else if (node->getName() == "client_max_body_size")
			handleClientMaxBodySize(node);
		else if (node->getName() == "return")
			handleReturn(node);
		/*else if (node->getName() == "root")
			handleRoot(node);
		else if (node->getName() == "autoindex")
			handleAutoIndex(node);
		else if (node->getName() == "deny")
			handleDeny(node);*/
	}
}

ConfigInterpreterRule*	ConfigInterpreter::getRule(std::vector<std::string>& context)
{
	for (size_t i = 0; i != rules_.size(); ++i)
	{
		if (rules_[i].getContext() == context)
			return (&rules_[i]);
	}
	return (0);
}

bool	ConfigInterpreter::isBlockValidInContext(std::string block, std::vector<std::string>& context)
{
    ConfigInterpreterRule* rule = getRule(context);
    if (rule)
		return (rule->isValidBlock(block));
    return false;
}

bool	ConfigInterpreter::isDirectiveValidInContext(std::string directive, std::vector<std::string>& context)
{
    ConfigInterpreterRule* rule = getRule(context);
    if (rule)
		return (rule->isValidDirective(directive));
    return false;
}

// =============================================================================
// Handlers
// =============================================================================

void	ConfigInterpreter::handleServerName(ConfigParserNode* node)
{
	std::cout << "handleServerName..." << std::endl;

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");
	configs_.back().setServerName(node->getParameters()[0]);
}
void	ConfigInterpreter::handleListen(ConfigParserNode* node)
{
	(void) node;
	std::cout << "handleListen..." << std::endl;

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

	std::string param = node->getParameters()[0];
	size_t colon_pos = param.find(':');
	if (colon_pos != std::string::npos)
	{
		std::string host = param.substr(0, colon_pos);

		if (!isIp(host))
			throw std::runtime_error("Directive `" + node->getName() + "` : host must be a valid IP");

		std::string port = param.substr(colon_pos + 1);

		if (!allOf(port, std::isdigit))
			throw std::runtime_error("Directive `" + node->getName() + "` : port must be a number");

		int p = toInt(port);

		if (p < 1 || p > 65535)
			throw std::runtime_error("Directive `" + node->getName() + "` : port number must be between 1 and 65535");
		
		configs_.back().setHost(host);
		configs_.back().setPort(toInt(port));
	}
	else
		throw std::runtime_error("Directive `" + node->getName() + "` : parameter must have the format `host:port`");

}
void	ConfigInterpreter::handleIndex(ConfigParserNode* node)
{
	(void) node;
	std::cout << "handleIndex..." << std::endl;

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");
}
void	ConfigInterpreter::handleErrorPage(ConfigParserNode* node)
{
	(void) node;
	std::cout << "handleErrorPage..." << std::endl;

	if (node->getParameters().size() >= 2)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have at least two parameters");
}
void	ConfigInterpreter::handleClientMaxBodySize(ConfigParserNode* node)
{
	(void) node;
	std::cout << "handleClientMaxBodySize..." << std::endl;

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");
}
void	ConfigInterpreter::handleReturn(ConfigParserNode* node)
{
	(void) node;
	std::cout << "handleReturn.." << std::endl;

	if (node->getParameters().size() != 2)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have 2 parameters");
}
