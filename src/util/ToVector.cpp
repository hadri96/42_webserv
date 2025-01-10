#include <ToVector.hpp>

std::vector<std::string> toVector(const char* array[])
{
	std::vector<std::string> result;
	for (const char** ptr = array; *ptr != NULL; ++ptr)
	{
		result.push_back(*ptr);
	}
	return (result);
}