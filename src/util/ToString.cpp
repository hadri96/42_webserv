#include "ToString.hpp"

#include <sstream>

std::string	toString(int n)
{
	std::stringstream ss;
	ss << n;
	return (ss.str());
}