#include <vector>
#include <string>

// General template for converting arrays to vectors
template <typename T, size_t N>
std::vector<T> toVector(T (&arr)[N])
{
	return std::vector<T>(arr, arr + N);
}

// Specialization for const char* to std::vector<std::string>
template <size_t N>
std::vector<std::string> toVector(const char* (&arr)[N])
{
	std::vector<std::string> vec;
	for (size_t i = 0; i < N; ++i)
	{
		vec.push_back(std::string(arr[i]));
	}
	return vec;
}

// Specialization for const char* array to std::vector<std::string>
std::vector<std::string> toVector(const char* array[])
{
	std::vector<std::string> vec;
	for (int i = 0; array[i] != 0; ++i)
	{
		vec.push_back(array[i]);
	}
	return vec;
}

// Correct specialization for converting an array of function pointers to std::vector
std::vector<void (*)(ConfigParserNode*)> toVector(void (*arr[])(ConfigParserNode*)) {
    std::vector<void (*)(ConfigParserNode*)> vec;
    for (int i = 0; arr[i] != 0; ++i) {  // Assumes array is terminated with a NULL pointer.
        vec.push_back(arr[i]);
    }
    return vec;
}