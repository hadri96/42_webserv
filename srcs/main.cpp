#include "webserv.hpp"

int	main(int argc, char **argv)
{
	int			port = 8080;
	EventLoop	server(port);

	(void) argc;
	(void) argv;

	server.run();
	return (0);
}
