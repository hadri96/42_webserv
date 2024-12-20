#include "ToInt.hpp"

#include <sstream>

int	toInt(std::string)
{
	std::stringstream ss;
	int n;

	ss >> n;
	return (n);
}
