#ifndef TO_VECTOR_HPP
# define TO_VECTOR_HPP

# include <stddef.h>
# include <vector>
# include <string>

/*template <typename T, size_t N>
std::vector<T> toVector(T (&arr)[N]);*/

std::vector<std::string> toVector(const char* array[]);

//# include "ToVector.tpp"

#endif