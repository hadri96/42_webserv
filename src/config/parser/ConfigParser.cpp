#include "ConfigParser.hpp"

#include "ConfigParserBlock.hpp"
#include "ConfigParserDirective.hpp"

#include <iostream>
#include <stdexcept>

#include "Logger.hpp"

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
	std::cout << "ConfigParser : destructor called" << std::endl;
	destroy();
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
// Setters and Getters
// =============================================================================

ConfigParserBlock*	ConfigParser::getRoot(void) const
{
	return (root_);
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
	Logger::logger()->logTitle(LOG_DEBUG, "Parsing the configuration file");
	displayBlock(root_);
}

void	ConfigParser::destroy(void)
{

	std::cout << "ConfigParser : destroy method called" << std::endl;
	if (lexer_)
	{
		delete lexer_;
		lexer_ = 0;
	}
	if (root_)
    {
        delete root_;
        root_ = 0;
    }
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
