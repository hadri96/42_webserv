#include "Webserv.hpp"

#include "File.hpp"
#include "ConfigLexer.hpp"

#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Webserv::Webserv(void)
{}

Webserv::Webserv(const Webserv& other)
{
	(void) other;
}

Webserv::Webserv(const std::string& configFile)
{
	File file(configFile);
	
	file.setContent();
	std::string content = file.getContent();

	std::cout << "Content : " << content; 

	ConfigLexer lexer = ConfigLexer();

	std::cout << "Lexer : " << std::endl;

	std::vector<ConfigToken> tokens = lexer.tokenize(content);

	lexer.displayTokens(tokens);
}

Webserv::~Webserv(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

Webserv&	Webserv::operator=(const Webserv& rhs)
{
	(void) rhs;
	return (*this);
}
