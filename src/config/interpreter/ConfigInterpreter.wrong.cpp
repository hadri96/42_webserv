#include "ConfigInterpreter.hpp"
#include "ToVector.hpp"
#include "ToInt.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigInterpreter::ConfigInterpreter(void)
{
	// Initialize valid blocks and directives for each context
	validBlocks_[toVector("root")] = toVector("events", "http");
	validBlocks_[toVector("root", "http")] = toVector("server");
	validBlocks_[toVector("root", "http", "server")] = toVector("location");
	validBlocks_[toVector("root", "http", "server", "location")] = toVector("limit_except");

	validDirectives_[toVector("root")] = toVector();
	validDirectives_[toVector("root", "http")] = toVector();
	validDirectives_[toVector("root", "http", "server")] = toVector("server_name", "listen", "index", "error_page", "client_max_body_size", "return");
	validDirectives_[toVector("root", "http", "server", "location")] = toVector("root", "autoindex", "index", "return");
	validDirectives_[toVector("root", "http", "server", "location", "limit_except")] = toVector("deny");

	// Initialize directive handlers
	directiveHandlers_["server_name"] = &ConfigInterpreter::handleServerName;
	directiveHandlers_["listen"] = &ConfigInterpreter::handleServerListen;
	directiveHandlers_["index"] = &ConfigInterpreter::handleServerIndex;
	directiveHandlers_["error_page"] = &ConfigInterpreter::handleServerErrorPage;
	directiveHandlers_["client_max_body_size"] = &ConfigInterpreter::handleServerClientMaxBodySize;
	directiveHandlers_["return"] = &ConfigInterpreter::handleServerReturn;
	// Add more handlers as needed
}

ConfigInterpreter::~ConfigInterpreter(void) {}

// =============================================================================
// Public Methods
// =============================================================================

Config ConfigInterpreter::interpret(ConfigParserBlock* root)
{
	std::vector<std::string> context;
	std::vector<ConfigParserNode*> nodes = root->getNodes();
	context.push_back(root->getName());
	
	for (size_t i = 0; i != nodes.size(); ++i)
	{
		interpret(nodes[i], context);
	}
	
	Config config;
	return config;
}

// =============================================================================
// Private Methods
// =============================================================================

void ConfigInterpreter::interpret(ConfigParserNode* node, std::vector<std::string>& context)
{
	ConfigParserBlock* block = dynamic_cast<ConfigParserBlock*>(node);
	
	if (block) {
		std::cout << "Block : `" << node->getName() << "` in context : `" << getDisplayableContext(context) << "`" << std::endl;

		if (!isBlockValidInContext(node->getName(), context))
			throw std::runtime_error("The block `" + node->getName() + "` is invalid in context `" + getDisplayableContext(context) + "`");

		std::vector<ConfigParserNode*> nodes = block->getNodes();
		context.push_back(block->getName());
		
		for (size_t i = 0; i != nodes.size(); ++i)
		{
			interpret(nodes[i], context);
		}

		context.pop_back();
	} else {
		std::cout << "\tDirective : `" << node->getName() << "` in context : `" << getDisplayableContext(context) << "`" << std::endl;

		if (!isDirectiveValidInContext(node->getName(), context))
			throw std::runtime_error("The directive `" + node->getName() + "` is invalid in context `" + getDisplayableContext(context) + "`");

		// Call the appropriate handler for the directive
		if (directiveHandlers_.find(node->getName()) != directiveHandlers_.end()) {
			(this->*directiveHandlers_[node->getName()])(node);
		}
	}
}

// =============================================================================
// Handlers
// =============================================================================

void ConfigInterpreter::handleServerName(ConfigParserNode* node)
{
	// Implementation for handling server_name
}

void ConfigInterpreter::handleServerListen(ConfigParserNode* node)
{
	// Implementation for handling listen
}

void ConfigInterpreter::handleServerIndex(ConfigParserNode* node)
{
	// Implementation for handling index
}

void ConfigInterpreter::handleServerErrorPage(ConfigParserNode* node)
{
	// Implementation for handling error_page
}

void ConfigInterpreter::handleServerClientMaxBodySize(ConfigParserNode* node)
{
	// Implementation for handling client_max_body_size
}

void ConfigInterpreter::handleServerReturn(ConfigParserNode* node)
{
	// Implementation for handling return
}

// =============================================================================
// Checkers
// =============================================================================

bool ConfigInterpreter::isBlockValidInContext(const std::string& block, const std::vector<std::string>& context)
{
	std::map<std::vector<std::string>, std::vector<std::string>>::iterator it = validBlocks_.find(context);
	if (it != validBlocks_.end()) {
		for (size_t i = 0; i != it->second.size(); ++i) {
			if (it->second[i] == block)
				return true;
		}
	}
	return false;
}

bool ConfigInterpreter::isDirectiveValidInContext(const std::string& directive, const std::vector<std::string>& context)
{
	std::map<std::vector<std::string>, std::vector<std::string>>::iterator it = validDirectives_.find(context);
	if (it != validDirectives_.end()) {
		for (size_t i = 0; i != it->second.size(); ++i) {
			if (it->second[i] == directive)
				return true;
		}
	}
	return false;
}

// =============================================================================
// Utility Functions
// =============================================================================

void ConfigInterpreter::addValidItemsToContext(
	const std::vector<std::string>& context,
	const std::vector<std::string>& validBlocks,
	const std::vector<std::string>& validDirectives
)
{
	validBlocks_[context] = validBlocks;
	validDirectives_[context] = validDirectives;
}

std::string ConfigInterpreter::getDisplayableContext(const std::vector<std::string>& context)
{
	std::string displayableContext;
	for (size_t i = 0; i != context.size(); ++i)
	{
		displayableContext.append(context[i]);
		if (i != context.size() - 1)
			displayableContext.append("->");
	}
	return displayableContext;
}