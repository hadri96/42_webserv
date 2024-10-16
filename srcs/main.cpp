#include "webserv.hpp"

int	main(int argc, char **argv)
{
	int			port = 8081;
	EventLoop	server(port);

	(void) argc;
	(void) argv;

	server.run();
	return (0);
}
