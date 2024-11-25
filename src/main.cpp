#include "Manager.hpp"
#include "Server.hpp"

int	main(void)
{

	Manager m;

	Server s1("127.0.0.1", 7272, &m);
	s1.start();
	Server s2("127.0.0.1", 7373, &m);
	s2.start();

	m.addServerToMonitor(&s1);
	m.addServerToMonitor(&s2);
	m.monitorEvents();

	return (0);
}