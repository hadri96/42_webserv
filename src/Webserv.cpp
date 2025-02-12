#include "Webserv.hpp"

#include "Logger.hpp"

#include "Path.hpp"
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
	std::string 			content = Path(configFile).getAbsPath().read();
	ConfigParser 			parser = ConfigParser(content);

	parser.parse();
	parser.display();

	ConfigInterpreter 		interpreter;
	interpreter.interpret(parser.getRoot());
	interpreter.displayConfigs();

	std::vector<Config> 	configs = interpreter.getConfigs();
	Observer* 				o = new Observer;
	std::vector<Server*> 	servers;

	/*
	const Location* foundLocation = configs[0].getLocation(Uri("/images"));
	if (!foundLocation)
	{
		std::cout << "LOCATION NOT FOUND\n\n";
	}
	else
	{
		std::cout << "LOCATION FOUND\n\n";
		std::cout << foundLocation->getRootPath().getPath();
	}
	*/

	Logger::logger()->logTitle(LOG_INFO, "Starting servers from configuration file");

	for (size_t i = 0; i != configs.size(); ++i)
	{
		// existingServer = getServer(configs[i].getHost(), configs[i].getPort())'
		// if (existingServer)
			// existingServer.addVirtualHost(configs[i])
		// else 
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
