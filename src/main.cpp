#include "Observer.hpp"
#include "Server.hpp"
#include "Logger.hpp"

int	main(void)
{
	Observer m;

	Server s1("127.0.0.1", 8084, &m);
	s1.start();
	Server s2("127.0.0.1", 8085, &m);
	s2.start();

	m.addServerToMonitor(&s1);
	m.addServerToMonitor(&s2);
	m.monitorEvents();

	return (0);
}