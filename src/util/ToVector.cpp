#include <vector>
#include <iostream>

template <typename T, size_t N>
std::vector<T> toVector(T (&arr)[N]) {
    // Use N to determine the size of the array
    std::vector<T> vec(arr, arr + N);
    return vec;
}
