#include "IsIp.hpp"
#include "ToInt.hpp"
#include <sstream>

bool isIp(const std::string& ip)
{
    // Split the string by '.' into parts
    std::stringstream ss(ip);
    std::string part;
    int count = 0;

    while (std::getline(ss, part, '.')) {
        // There must be exactly 4 parts
        if (++count > 4)
            return (false);

        // Check if the part is a valid number and falls within the range [0, 255]
        if (part.empty()) return false;  // Part cannot be empty
        for (size_t i = 0; i < part.size(); ++i)
		{
            if (!std::isdigit(part[i]))
                return (false);
        }

        // Convert part to integer and check the range [0, 255]
        int num = toInt(part);
        if (num < 0 || num > 255 || (part.size() > 1 && part[0] == '0'))
            return (false);
    }

    // The IP address must contain exactly 4 parts
    return count == 4;
}