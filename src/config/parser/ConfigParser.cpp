#include "ConfigParser.hpp"

#include "ConfigParserBlock.hpp"
#include "ConfigParserDirective.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParser::ConfigParser(void)
{}

ConfigParser::ConfigParser(const ConfigParser& other)
{}

ConfigParser::~ConfigParser(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigParser&	ConfigParser::operator=(const ConfigParser& rhs)
{}

// =============================================================================
// Public Methods
// =============================================================================

void	ConfigParser::parse(std::vector<ConfigToken>& tokens)
{
	size_t				index;
	ConfigParserBlock*	root;

	index = 0;

	parseBlock(tokens, root, index);
}

// =============================================================================
// Private Methods
// =============================================================================

void	ConfigParser::parseBlock(std::vector<ConfigToken>& tokens, ConfigParserBlock* parent, size_t& index)
{
	while (index != tokens.size())
	{
		if (tokens[index] == CT_KEYWORD)
		{
			std::string					keyword;
			std::vector<std::string>	parameters;

			keyword = tokens[index].getValue();

			// Loop through the parameters
			while (index != tokens.size())
			{
				if (tokens[index] == CT_KEYWORD)
					parameters.push_back(tokens[index].getValue());
				else if (tokens[index] == CT_LEFT_BRACE)
				{
					// Triggers block creation
					ConfigParserBlock block = ConfigParserBlock(keyword, parameters);
					parent->addNode(block);
					
					parseBlock(tokens, &block, index);
					if (tokens[index] == CT_RIGHT_BRACE)
					{
						// close block
						break;
					}
					break ;
				}
				else if (tokens[index] == CT_SEMICOLON)
				{
					// Triggers directive creation
					ConfigParserDirective directive = ConfigParserDirective(keyword, parameters);
					parent->addNode(directive);
					break ;
				}
				++index;
			}
		}
		++index;
	}
}