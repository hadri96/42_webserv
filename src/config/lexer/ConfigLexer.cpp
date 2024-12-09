#include "ConfigLexer.hpp"
#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigLexer::ConfigLexer(void)
{}

ConfigLexer::ConfigLexer(const ConfigLexer& other)
{
	(void) other;
}

ConfigLexer::~ConfigLexer(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigLexer&	ConfigLexer::operator=(const ConfigLexer& rhs)
{
	(void) rhs;
	return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

std::vector<ConfigToken>	ConfigLexer::tokenize(const std::string& input)
{
	std::vector<ConfigToken>	tokens;
	size_t						i;
	char						current;

	i = 0;
	while (i != input.size())
	{
		current = input[i];

		if (isspace(current))
			++i;
		else if (isKeyword(current))
		{
			std::string keyword;

			while (i != input.size() && isKeyword(input[i]))
			{
				keyword += input[i];
				++i;
			}

			tokens.push_back(ConfigToken(CT_KEYWORD, keyword));
		}
		else if (current == '{')
		{
			tokens.push_back(ConfigToken(CT_LEFT_BRACE, "{"));
			++i;
		}
		else if (current == '}')
		{
			tokens.push_back(ConfigToken(CT_RIGHT_BRACE, "}"));
			++i;
		}
		else if (current == ';')
		{
			tokens.push_back(ConfigToken(CT_SEMICOLON, ";"));
			++i;
		}
		else
		{
			// Unexpected character
			++i;
		}
	}

	return (tokens);
}

void	ConfigLexer::displayTokens(std::vector<ConfigToken> tokens)
{
	for (size_t i = 0; i != tokens.size(); ++i)
	{
		std::cout << "Type : " << tokens[i].getType() << " Value : " << tokens[i].getValue() << std::endl;
	}
}

// =============================================================================
// Private Methods
// =============================================================================

bool	ConfigLexer::isKeyword(char c)
{
	return (isprint(c) && !(isspace(c)) && c != ';' && c != '{' && c != '}');
}
