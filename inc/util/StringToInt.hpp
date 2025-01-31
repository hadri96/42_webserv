#ifndef STRING_TO_INT_HPP
#define STRING_TO_INT_HPP

#include <string>
#include <sstream>

class StringToInt 
{
    public:
        static int stoi(const std::string &str, bool *success = NULL);
};

#endif
