#ifndef TO_VECTOR_HPP
# define TO_VECTOR_HPP

# include <stddef.h>
# include <vector>

template <typename T, size_t N>
std::vector<T> toVector(T (&arr)[N]);

template <size_t N>
std::vector<std::string> toVector(const char* (&arr)[N]);

# include "ToVector.tpp"

#endif