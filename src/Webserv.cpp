#include "Webserv.hpp"

#include "File.hpp"
#include "ConfigLexer.hpp"
#include "ConfigParser.hpp"
#include "ConfigInterpreter.hpp"

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

	ConfigParser parser = ConfigParser(content);
	parser.parse();
	parser.display();

	ConfigInterpreter interpreter;
	interpreter.interpret(parser.getRoot());
	interpreter.displayConfigs();
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
