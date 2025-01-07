

#include <ToVector.hpp>

// General template for converting arrays to vectors
/*template <typename T, size_t N>
std::vector<T> toVector(T (&arr)[N])
{
	return std::vector<T>(arr, arr + N);
}*/

// Utility function to convert null-terminated C-style arrays to std::vector
std::vector<std::string> toVector(const char* array[])
{
	std::vector<std::string> result;
	for (const char** ptr = array; *ptr != NULL; ++ptr)
	{
		result.push_back(*ptr);
	}
	return (result);
}