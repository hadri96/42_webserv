#include "AllOf.hpp"

bool	allOf(std::string str, int (*func)(int c))
{
	for (size_t i = 0; i != str.size(); ++i)
	{
		if (!func(static_cast<unsigned char>(str[i])))
			return (false);
	}
	return (true);
}
