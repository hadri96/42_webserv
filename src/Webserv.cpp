#include "Webserv.hpp"

#include "File.hpp"
#include "ConfigLexer.hpp"
#include "ConfigParser.hpp"
#include "ConfigInterpreter.hpp"

#include "Observer.hpp"
#include "Server.hpp"

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

	std::vector<Config> configs = interpreter.getConfigs();
	Observer* o = new Observer;
	std::vector<Server*> servers;

	Logger::logger()->logTitle(LOG_INFO, "Starting servers from configuration file");

	for (size_t i = 0; i != configs.size(); ++i)
	{
		servers.push_back(new Server(configs[i], o));
	}

	std::ostringstream oss;
	for (size_t i = 0; i != servers.size(); ++i)
	{
		oss << "Starting server no. " << (i + 1) << " : " << servers[i]->getInfoUrl();
		Logger::logger()->logTitle(LOG_INFO, oss, 2);
		servers[i]->start();
		o->addServerToMonitor(servers[i]);
	}
	o->monitorEvents();
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
