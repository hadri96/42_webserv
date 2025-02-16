#include "Webserv.hpp"

#include "Logger.hpp"

#include "Path.hpp"
#include "ConfigLexer.hpp"
#include "ConfigParser.hpp"
#include "ConfigInterpreter.hpp"

#include "Observer.hpp"
#include "Server.hpp"

#include "ToString.hpp"

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

	configs_ = interpreter.getConfigs();
	parser.destroy();

	Observer* 				o = new Observer;

	for (size_t i = 0; i != configs_.size(); ++i)
	{
		Server* existingServer = getServer(configs_[i].getHost(), configs_[i].getPort());
		if (existingServer)
		{
			Logger::logger()->log(LOG_DEBUG, "Adding virtual host");;
			existingServer->addVirtualHost(configs_[i]);
		}
		else
			servers_.push_back(new Server(configs_[i], o));
	}

	checkForInvalidServer();

	Logger::logger()->logTitle(LOG_INFO, "Starting servers from configuration file");
	std::ostringstream oss;
	for (size_t i = 0; i != servers_.size(); ++i)
	{
		oss << "Starting server no. " << (i + 1) << " : " << servers_[i]->getInfoUrl();
		Logger::logger()->logTitle(LOG_INFO, oss, 2);
		servers_[i]->start();
		o->addServerToMonitor(servers_[i]);
	}
	o->monitorEvents();
	if (o)
	{
		delete o;
		o = 0;
	}
}

Webserv::~Webserv(void)
{
	std::cout << "Webserv : destructor called" << std::endl;

	for (size_t i = 0; i != servers_.size(); ++i)
	{
		if (servers_[i])
		{
			delete servers_[i];
			servers_[i] = 0;
		}		
			
	}
	servers_.clear();
}

// =============================================================================
// Operators Overload
// =============================================================================

Webserv&	Webserv::operator=(const Webserv& rhs)
{
	(void) rhs;
	return (*this);
}

// =============================================================================
// Private Methods
// =============================================================================

Server*		Webserv::getServer(const std::string& host, int port)
{
	for (size_t i = 0; i != servers_.size(); ++i)
	{
		if (servers_[i]->getInfoHostPort() == "[" + host + ":" + toString(port) + "]") // REVISIT : use another getter
			return (servers_[i]);
	}
	return (0);
}

void	Webserv::checkForInvalidServer(void)
{
	size_t serverCount = servers_.size();

	if (serverCount < 1)
		throw std::runtime_error("Configuration : must have at least one server block and one listen directive");

	for (size_t i = 0; i != serverCount; ++i)
	{
		if (servers_[i]->getInfoHostPort() == "[localhost:0]")
			throw std::runtime_error("Configuration : found a server block with no listen directive");
	}
}
