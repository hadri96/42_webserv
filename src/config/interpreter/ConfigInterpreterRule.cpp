#include "ConfigInterpreterRule.hpp"
#include "ConfigInterpreter.hpp"

#include "ToVector.hpp"
#include "Join.hpp"

#include "Colors.hpp"

#include <vector>
#include <string>
#include <ostream>
#include <iostream>

#include <sstream> // std::ostringstream
#include "Logger.hpp"


// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigInterpreterRule::ConfigInterpreterRule(void)
{}

ConfigInterpreterRule::ConfigInterpreterRule(const ConfigInterpreterRule& other)
{
	context_ = other.context_;
	validBlocks_ = other.validBlocks_;
	validDirectives_ = other.validDirectives_;
}

ConfigInterpreterRule::ConfigInterpreterRule(
	const char* context[],
	const char* validBlocks[],
	const char* validDirectives[]//,
	//void (ConfigInterpreter::*handlers[])(ConfigParserNode* node)
) :
	context_(toVector(context)),
	validBlocks_(toVector(validBlocks)),
	validDirectives_(toVector(validDirectives))//,
	//handlers_(toVector(handlers))
{}

ConfigInterpreterRule::~ConfigInterpreterRule(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigInterpreterRule&	ConfigInterpreterRule::operator=(const ConfigInterpreterRule& rhs)
{
	(void) rhs;
	return (*this);
}

/*std::ostream&	operator<<(std::ostream& os, const ConfigInterpreterRule& object)
{
	os << "--- Rule for context :" << C_YEL << join(object.getContext(), "->") << RESET << " ---" << std::endl;
	os << "  Valid blocks in context : " C_YEL << join(object.getValidBlocks(), ", ") << RESET << std::endl;
	os << "  Valid directives in context : " C_YEL << join(object.getValidDirectives(), ", ") << RESET;
	return (os);
}*/

void	ConfigInterpreterRule::log(void)
{
	std::ostringstream oss;

	Logger::logger()->logTitle(LOG_DEBUG, "Settings for the configuration interpreter rules");

	oss << "Rule for context : " << join(getContext(), "->");
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  Valid blocks in context : " << join(getValidBlocks(), ", ");
	Logger::logger()->log(LOG_DEBUG, oss);

	oss << "  Valid directives in context : " << join(getValidDirectives(), ", ");
	Logger::logger()->log(LOG_DEBUG, oss);
}

// =============================================================================
// Setters and Getters
// =============================================================================

const std::vector<std::string>&	ConfigInterpreterRule::getContext(void) const
{
	return (context_);
}

const std::vector<std::string>&	ConfigInterpreterRule::getValidBlocks(void) const
{
	return (validBlocks_);
}

const std::vector<std::string>&	ConfigInterpreterRule::getValidDirectives(void) const
{
	return (validDirectives_);
}

// =============================================================================
// Public Methods
// =============================================================================

bool	ConfigInterpreterRule::isValidBlock(std::string block) const
{
	for (size_t i = 0; i != validBlocks_.size(); ++i)
	{
		if (validBlocks_[i] == block)
			return (true);
	}
	return (false);
}

bool	ConfigInterpreterRule::isValidDirective(std::string block) const
{
	for (size_t i = 0; i != validDirectives_.size(); ++i)
	{
		if (validDirectives_[i] == block)
			return (true);
	}
	return (false);
}