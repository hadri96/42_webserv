#include "StringToInt.hpp"

int StringToInt::stoi(const std::string &str, bool *success) 
{
    std::stringstream   ss(str);
    int                 result = 0;

    ss >> result;

    if (ss.fail() || !ss.eof()) 
    {
        if (success) 
            *success = false;
        return (0);
    }

    if (success) *success = true;

    return (result);
}

