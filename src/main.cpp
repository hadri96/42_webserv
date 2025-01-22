#include "Webserv.hpp"
#include "Observer.hpp"
#include "Server.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#include <iostream>

#include "PathOrUri.hpp"
#include "Path.hpp"


int	main(int argc, char** argv)
{

	std::string configPath;

	if (argc == 1)
		configPath = "conf/complex.conf";
	else if (argc == 2)
		configPath = argv[1];

	try
	{
		Webserv webserv(configPath);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
