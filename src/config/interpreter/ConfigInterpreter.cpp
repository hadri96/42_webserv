/*
 TO DO :

 handle redirections outside a Location... OK
 handle error pages
 handle limit_except
 
*/

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
#include <algorithm>

#include <sstream> // std::ostringstream
#include "Logger.hpp"

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
	const char*	blocks3[]		= {"location", "cgi", 0};
	const char* directives3[]	= {"server_name", "listen", "error_page", "client_max_body_size", 0};

	// --- Context : root, http, server, location ---
	const char* context4[]		= {"root", "http", "server", "location", 0};
	const char* blocks4[]		= {"limit_except", 0};
	const char* directives4[]	= {"root", "autoindex", "index", "return", "client_max_body_size", 0};

	// --- Context : root, http, server, cgi ---
	const char* context5[]		= {"root", "http", "server", "cgi", 0};
	const char* blocks5[]		= {0};
	const char* directives5[]	= {"cgi_exec", "cgi_params", 0};
	
	// --- Context : root, http, server, location, limit_except ---
	const char* context6[]		= {"root", "http", "server", "location", "limit_except", 0};
	const char* blocks6[]		= {0};
	const char* directives6[]	= {"deny", 0};

	addRule(ConfigInterpreterRule(context1, blocks1, directives1));
	addRule(ConfigInterpreterRule(context2, blocks2, directives2));
	addRule(ConfigInterpreterRule(context3, blocks3, directives3));
	addRule(ConfigInterpreterRule(context4, blocks4, directives4));
	addRule(ConfigInterpreterRule(context5, blocks5, directives5));
	addRule(ConfigInterpreterRule(context6, blocks6, directives6));

	for (size_t i = 0; i != rules_.size(); ++i)
	{
		rules_[i].log();
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
// Getters and Setters
// =============================================================================

std::vector<Config>&	ConfigInterpreter::getConfigs(void)
{
	return (configs_);
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

	Logger::logger()->logTitle(LOG_DEBUG, "Configuration interpreter");

	nodes = root->getNodes();
	context.push_back(root->getName());
	for (size_t i = 0; i != nodes.size(); ++i)
	{
		interpret(nodes[i], context);
	}
	Config config;
	return (config);
}

void	ConfigInterpreter::displayConfigs(void)
{
	for (size_t i = 0; i != configs_.size(); ++i)
	{
		//std::cout << C_BLU << configs_[i] << RESET << std::endl;
		configs_[i].log();
	}
}

// =============================================================================
// Private Methods
// =============================================================================

void	ConfigInterpreter::interpret(
	ConfigParserNode* node,
	std::vector<std::string>& context)
{
	ConfigParserBlock* block = dynamic_cast<ConfigParserBlock*>(node);
	std::ostringstream oss;

	std::string	parent = context.back();

	// --- Block ---
	if (block)
	{
		oss << "Block : [`" << node->getName() << "`] in context : `" << join(context, "->") << "`";
		Logger::logger()->log(LOG_DEBUG, oss);

		if (!isBlockValidInContext(node->getName(), context))
			throw std::runtime_error("The block `" + node->getName() + "` is invalid in context `" + join(context, "->") + "`");

		// --- Handle block ---
		handleBlock(node);

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
		oss << " - Directive : [`" << node->getName() << "`] in context : `" << join(context, "->") << "`";
		Logger::logger()->log(LOG_DEBUG, oss);

		if (!isDirectiveValidInContext(node->getName(), context))
			throw std::runtime_error("The directive `" + node->getName() + "` is invalid in context `" + join(context, "->") + "`");

		// --- Handle directive ---
		handleDirective(node, parent);
	}

	if (hasDuplicateConfig())
	{
		Logger::destroy();
		throw std::runtime_error("Duplicate server block found (same host, port and server_name)"); // REVISIT : need to free memory
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

bool	ConfigInterpreter::hasDuplicateConfig(void)
{
	if (currentConfig_ < 1)
		return (false);

	size_t current = currentConfig_;
	size_t previous = currentConfig_ - 1;

	if (configs_[current].getHost() == configs_[previous].getHost() && 
		configs_[current].getPort() == configs_[previous].getPort() &&
		configs_[current].getServerName() == configs_[previous].getServerName())
		return (true);

	return (false);
}

// =============================================================================
// Handlers
// =============================================================================

void	ConfigInterpreter::handleBlock(ConfigParserNode* node)
{
	Config& currentConfig = configs_.back();

	if (node->getName() == "server")
	{
		++currentConfig_;
		Config newConfig;
		configs_.push_back(newConfig);
	}
	else if (node->getName() == "location")
	{
		if (node->getParameters().size() != 1)
			throw std::runtime_error("Block `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

		ConfigLocation newLocation;
		currentConfig.addConfigLocation(newLocation);
		
		ConfigLocation& currentLocation = currentConfig.getConfigLocations().back();
		currentLocation.setUri(Uri(node->getParameters()[0]));
	}
	else if (node->getName() == "cgi")
	{
		ConfigCgi newCgi;
		size_t parametersCount = node->getParameters().size();

		if (parametersCount < 1)
			throw std::runtime_error("Block `" + node->getName() + "` : wrong number of parameter ; must have at least one parameter");
		
		for (size_t i = 0; i != parametersCount; ++i)
		{
			std::string current = node->getParameters()[i];
		
			if (current[0] && current[0] != '.')
				throw std::runtime_error(node->getName() + " : extension must have exactly one dot at the beginning");


			current = current.substr(1);
			for (size_t i = 0; i != current.length(); ++i)
			{
				if (current[i] == '.')
					throw std::runtime_error(node->getName() + " : extension must have exactly one dot at the beginning");
			}
			
			newCgi.addExtension(current);
		}
		currentConfig.addConfigCgi(newCgi);
	}
	else if (node->getName() == "limit_except")
	{
		ConfigLocation& currentLocation = currentConfig.getConfigLocations().back();

		for (size_t i = 0; i != node->getParameters().size(); ++i)
		{
			std::string httpMethodTypeStr = node->getParameters()[i];
			HttpMethodType httpMethodType = stringToHttpMethod(httpMethodTypeStr);
			if (httpMethodType == UNKNOWN)
				throw std::runtime_error("Directive `" + node->getName() + "` : wrong method name");
			currentLocation.addAllowedMethod(httpMethodType);
		}
	}
}

void	ConfigInterpreter::handleDirective(ConfigParserNode* node, const std::string& parent)
{
	if (node->getName() == "server_name")
		handleServerName(node);
	else if (node->getName() == "listen")
		handleListen(node);
	else if (node->getName() == "index")
		handleIndex(node);
	else if (node->getName() == "error_page")
		handleErrorPage(node);
	else if (node->getName() == "client_max_body_size")
		handleClientMaxBodySize(node, parent);
	else if (node->getName() == "return")
		handleReturn(node);
	else if (node->getName() == "root")
		handleRoot(node);
	else if (node->getName() == "autoindex")
		handleAutoIndex(node);
	else if (node->getName() == "index")
		handleIndex(node);
	else if (node->getName() == "deny")
		handleDeny(node);
	else if (node->getName() == "cgi_exec")
		handleCgiExec(node);
	else if (node->getName() == "cgi_params")
		handleCgiParams(node);
}

// --- Directive handlers ---

void	ConfigInterpreter::handleServerName(ConfigParserNode* node)
{
	//std::cout << "handleServerName..." << std::endl;

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");
	configs_.back().setServerName(node->getParameters()[0]);
}
void	ConfigInterpreter::handleListen(ConfigParserNode* node)
{
	//std::cout << "handleListen..." << std::endl;

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
	//std::cout << "handleIndex..." << std::endl;

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

	Config& currentConfig = configs_.back();
	ConfigLocation& currentLocation = currentConfig.getConfigLocations().back();

	currentLocation.setDefaultFile(node->getParameters()[0]);
}
void	ConfigInterpreter::handleErrorPage(ConfigParserNode* node)
{
	(void) node;
	//std::cout << "handleErrorPage..." << std::endl;

	std::vector<int>	errorCodes;
	std::string			uri;

	if (node->getParameters().size() < 2)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have at least two parameters");

	for (size_t i = 0; i != node->getParameters().size() - 1; ++i)
	{
		if (!allOf(node->getParameters()[i], std::isdigit))
			throw std::runtime_error("Directive `" + node->getName() + "` : status code errors must be numbers");
		errorCodes.push_back(toInt(node->getParameters()[i]));
	}

	uri = node->getParameters().back();
	//std::cout << uri << std::endl;

	for (size_t i = 0; i != errorCodes.size(); ++i)
	{
		configs_.back().addConfigErrorPage(ConfigErrorPage(errorCodes[i], Uri(uri)));
	}
}
void	ConfigInterpreter::handleClientMaxBodySize(ConfigParserNode* node, const std::string& parent)
{
    (void) node;
    //std::cout << "handleClientMaxBodySize..." << std::endl;

    if (node->getParameters().size() != 1)
        throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

    std::string parameter = node->getParameters()[0];
    size_t len = parameter.size();

    if (len == 0)
        throw std::runtime_error("Directive `" + node->getName() + "` : parameter cannot be empty");

    char unit = parameter[len - 1];
    int factor = 1;
    std::string numberPart = parameter;

    if (!std::isdigit(unit))
    {
        if (unit == 'M' || unit == 'm')
            factor = 1048576;
        else if (unit == 'K' || unit == 'k')
            factor = 1024;
        else
            throw std::runtime_error("Directive `" + node->getName() + "` : wrong unit ; must be `M/m`, `K/k` or none (size given in bytes)");

        numberPart = parameter.substr(0, len - 1);
    }

    if (!allOf(numberPart, std::isdigit))
        throw std::runtime_error("Directive `" + node->getName() + "` : size must be a number with or without unit (`M/m` or `K/k`)");
	else

	if (parent == "server")
		configs_.back().setClientMaxBodySize(factor * toInt(numberPart));
	else if (parent == "location")
		configs_.back().getConfigLocations().back().setClientMaxBodySize(factor * toInt(numberPart));
}
void	ConfigInterpreter::handleReturn(ConfigParserNode* node)
{
	if (node->getParameters().size() != 2) // also could be 1 parameter ; see that case later
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have 2 parameters");

	std::string statusCodePart = node->getParameters()[0];

    if (!allOf(statusCodePart, std::isdigit))
		throw std::runtime_error("Directive `" + node->getName() + "` : status code must be a number");
	
	int statusCode = toInt(statusCodePart);

	if (statusCode != 301 && statusCode != 302)
		throw std::runtime_error("Directive `" + node->getName() + "` : invalid status code");

	std::string uri = node->getParameters()[1];

	/*if (parent == "server")
		configs_.back().setConfigRedirection(ConfigRedirection(statusCode, Uri(uri)));
	else if (parent == "location")*/

	configs_.back().getConfigLocations().back().setConfigRedirection(ConfigRedirection(statusCode, Uri(uri)));
		
}

// --- Handle location ---

void	ConfigInterpreter::handleRoot(ConfigParserNode* node)
{
	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

	Config& currentConfig = configs_.back();
	ConfigLocation& currentLocation = currentConfig.getConfigLocations().back();

	currentLocation.setRootPath(Path(node->getParameters()[0]));
}

void	ConfigInterpreter::handleAutoIndex(ConfigParserNode* node)
{
	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

	if (node->getParameters()[0] != "on" && node->getParameters()[0] != "off")
		throw std::runtime_error("Directive `" + node->getName() + "` : parameter must be either `on` or `off");

	Config& currentConfig = configs_.back();
	ConfigLocation& currentLocation = currentConfig.getConfigLocations().back();

	if (node->getParameters()[0] == "on")
		currentLocation.setAutoIndex(true);
	else
		currentLocation.setAutoIndex(false);
}

void	ConfigInterpreter::handleDeny(ConfigParserNode* node)
{
	(void) node;
}

void	ConfigInterpreter::handleCgiExec(ConfigParserNode* node)
{
	Config& currentConfig = configs_.back();
	ConfigCgi& currentCgi = currentConfig.getConfigCgi();

	if (node->getParameters().size() != 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have one parameter");

	currentCgi.setExecutable(Path(node->getParameters()[0]));
}

void	ConfigInterpreter::handleCgiParams(ConfigParserNode* node)
{
	Config& currentConfig = configs_.back();
	ConfigCgi& currentCgi = currentConfig.getConfigCgi();

	if (node->getParameters().size() < 1)
		throw std::runtime_error("Directive `" + node->getName() + "` : wrong number of parameter ; must have at least one parameter");

	std::string parameters;
	for (size_t i = 0; i != node->getParameters().size(); ++i)
	{
		parameters.append(node->getParameters()[i]);
		if (i != node->getParameters().size() - 1)
			parameters.append(" ");
	}
	currentCgi.setParameters(parameters);
}