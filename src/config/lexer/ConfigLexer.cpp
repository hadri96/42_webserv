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

ConfigLexer::ConfigLexer(const std::string& input) :
	input_(input),
	position_(0)
{}

ConfigLexer::~ConfigLexer(void)
{
	std::cout << "ConfigLexer : destructor called" << std::endl;
}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigLexer&	ConfigLexer::operator=(const ConfigLexer& rhs)
{
	(void) rhs;
	return (*this);
}

// =============================================================================
// Setters and Getters
// =============================================================================

/*
const std::vector<ConfigToken>&	ConfigLexer::getTokens(void) const
{
	return (tokens_);
}
*/

// =============================================================================
// Public Methods
// =============================================================================

/*
void	ConfigLexer::tokenize(const std::string& input)
{
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

			tokens_.push_back(ConfigToken(CT_KEYWORD, keyword));
		}
		else if (current == '{')
		{
			tokens_.push_back(ConfigToken(CT_LEFT_BRACE, "{"));
			++i;
		}
		else if (current == '}')
		{
			tokens_.push_back(ConfigToken(CT_RIGHT_BRACE, "}"));
			++i;
		}
		else if (current == ';')
		{
			tokens_.push_back(ConfigToken(CT_SEMICOLON, ";"));
			++i;
		}
		else
		{
			// Unexpected character
			++i;
		}
	}
}
*/

/*
void	ConfigLexer::display(void) const
{
	for (size_t i = 0; i != tokens_.size(); ++i)
	{
		std::cout 
			<< "Type : " << tokens_[i].getType() 
			<< " Value : " << tokens_[i].getValue() << std::endl;
	}
}
*/

ConfigToken	ConfigLexer::nextToken(void)
{
	char	current;

	while (position_ != input_.size())
	{
		current = input_[position_];

		if (isspace(current))
			++position_;
		else if (isKeyword(current))
		{
			std::string keyword;

			while (position_ != input_.size() && isKeyword(input_[position_]))
			{
				keyword += input_[position_];
				++position_;
			}
			return(ConfigToken(CT_KEYWORD, keyword));
		}
		else if (current == '{')
		{
			++position_;
			return(ConfigToken(CT_LEFT_BRACE, "{"));
		}
		else if (current == '}')
		{
			++position_;
			return(ConfigToken(CT_RIGHT_BRACE, "}"));
		}
		else if (current == ';')
		{
			++position_;
			return(ConfigToken(CT_SEMICOLON, ";"));
		}
		else if (current == '#')
		{
			while (position_ != input_.size() && input_[position_] != '\n')
			{
				++position_;
			}
		}
		else
		{
			// Unexpected character
			++position_;
			return(ConfigToken(CT_UNDEFINED, ";"));
		}	
	}
	return (ConfigToken(CT_EOF, ""));
}

// =============================================================================
// Private Methods
// =============================================================================

bool	ConfigLexer::isKeyword(char c) const
{
	return (isprint(c) && !(isspace(c)) && c != ';' && c != '{' && c != '}' && c != '#');
}