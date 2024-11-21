#include "webserv.hpp"

int	main(int argc, char **argv)
{
	Manager		manager;
	Config		config;

	(void) argc;
	(void) argv;

	manager.initialise(config);
	manager.run();
	return (0);
}
