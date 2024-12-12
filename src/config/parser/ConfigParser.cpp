#include "ConfigParser.hpp"

#include "ConfigParserBlock.hpp"
#include "ConfigParserDirective.hpp"

#include <iostream>
#include <stdexcept>

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigParser::ConfigParser(void) :
	root_(0),
	lexer_(0),
	currentToken_(CT_UNDEFINED, "")
{}

ConfigParser::ConfigParser(const ConfigParser& other) :
	root_(other.root_),
	lexer_(other.lexer_),
	currentToken_(other.currentToken_)
{}

ConfigParser::ConfigParser(const std::string& input) :
	root_(0)
{
	lexer_ = new ConfigLexer(input);
	currentToken_ = lexer_->nextToken(); 
}

ConfigParser::~ConfigParser(void)
{
	//delete root_;
	delete lexer_;
}

// =============================================================================
// Operators Overload
// =============================================================================

// Must be a deep copy
ConfigParser&	ConfigParser::operator=(const ConfigParser& rhs)
{
	if (this == &rhs)
		return (*this);
	
	root_ = rhs.root_;
	lexer_ = rhs.lexer_;
	return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

void	ConfigParser::parse(void)
{
	root_ = new ConfigParserBlock();

	parseBlock(root_, 1);
}

void	ConfigParser::display(void)
{
	displayBlock(root_);
}


// =============================================================================
// Private Methods
// =============================================================================

void	ConfigParser::displayBlock(ConfigParserBlock* block)
{
	if (block)
		block->display();
}

void	ConfigParser::consume(ConfigTokenType expectedToken)
{
	if (currentToken_ == expectedToken)
		currentToken_ = lexer_->nextToken();
	else 
		throw std::runtime_error("Lexer : Unexpected token in grammar");
}
/*
 * Potential improvments :
 * - Set a maximum nesting
 */
void ConfigParser::parseBlock(ConfigParserBlock* parent, int openBlockCount)
{
	while (currentToken_ != CT_EOF)
	{
		if (currentToken_ == CT_KEYWORD)
		{
			std::string					keyword;
			std::vector<std::string>	parameters;

			keyword = currentToken_.getValue();

			consume(CT_KEYWORD);
			while (currentToken_ == CT_KEYWORD)
			{
				parameters.push_back(currentToken_.getValue());
				consume(CT_KEYWORD);
			}
			// Expects a semicolon or a left brace
			if (currentToken_ == CT_SEMICOLON)
			{
				ConfigParserDirective* directive = new ConfigParserDirective(keyword, parameters);
				parent->addNode(directive);
				consume(CT_SEMICOLON);
			}
			else if (currentToken_ == CT_LEFT_BRACE)
			{
				ConfigParserBlock* block = new ConfigParserBlock(keyword, parameters);
				parent->addNode(block);
				consume(CT_LEFT_BRACE);
				parseBlock(block, ++openBlockCount);
			}
			else
				throw std::runtime_error("Expected semicolon or right brace after a keyword.");
		}
		else if (currentToken_ == CT_RIGHT_BRACE)
		{
			consume(CT_RIGHT_BRACE);
			if (openBlockCount > 0)
			{
				--openBlockCount;
				return ;
			}
			else
				throw std::runtime_error("Unexpected right brace, too many closing brackets.");
		}
		else if (currentToken_ == CT_EOF)
		{
			if (openBlockCount == 0)
				return ;
			else
				throw std::runtime_error("Missing right braces. Remaining open blocks.");
		}
	}

}



/*void	ConfigParser::parseBlock(
			const std::vector<ConfigToken>& tokens,
			ConfigParserBlock* parent,
			size_t& index)
{
	while (index != tokens.size())
	{
		if (tokens[index] == CT_KEYWORD)
		{
			std::cout << "KEYWORD" << std::endl;
			std::string					keyword;
			std::vector<std::string>	parameters;

			keyword = tokens[index].getValue();
			std::cout << "keyword : " << keyword << std::endl;
			
			// Loop through the parameters
			++index;
			while (index != tokens.size())
			{
				std::cout << "TYPE : " << tokens[index].getType() << " VALUE : `" << tokens[index].getValue() << "`" << std::endl;
				if (tokens[index] == CT_KEYWORD)
				{
					std::string parameter = tokens[index].getValue();
					std::cout << "parameter : " << parameter << std::endl;
					parameters.push_back(parameter);
				}
				else if (tokens[index] == CT_LEFT_BRACE)
				{
					std::cout << "LEFT_BRACE" << std::endl;
					// Triggers block creation
					ConfigParserBlock* block = new ConfigParserBlock(keyword, parameters);
					parent->addNode(block);
					
					parseBlock(tokens, block, index);
					if (tokens[index] == CT_RIGHT_BRACE)
					{
						std::cout << "RIGHT_BRACE" << std::endl;
						// close block
						++index;
						break;
					}
				}
				else if (tokens[index] == CT_SEMICOLON)
				{
					std::cout << "SEMICOLON" << std::endl;
					// Triggers directive creation
					ConfigParserDirective* directive = new ConfigParserDirective(keyword, parameters);
					parent->addNode(directive);
					++index;
					break ;
				}
				++index;
			}
		}
		++index;
	}
}*/

/*void	ConfigParser::parseBlock(
			const std::vector<ConfigToken>& tokens,
			ConfigParserBlock* parent,
			size_t& index)
{
	bool	isInKeyword;

	isInKeyword = false;

	// First token must be a keyword
	if (tokens[index] != CT_KEYWORD)
		return ;

	while (index != tokens.size())
	{
		std::string					keyword;
		std::vector<std::string>	parameters;
		if (tokens[index] == CT_KEYWORD)
		{
			if (!isInKeyword)
			{
				// Handle keyword
				isInKeyword = true;
			}
			else
			{
				// Handle parameters
			}
		}
		else if (tokens[index] == CT_LEFT_BRACE)
		{
			
		}
		else if (tokens[index] == CT_SEMICOLON)
		{
			isInKeyword = false;
		}

		++index;
	}
	
	std::cout << "KEYWORD" << std::endl;

	std::string					keyword;
	std::vector<std::string>	parameters;

	keyword = tokens[index].getValue();
	std::cout << "keyword : " << keyword << std::endl;


}*/