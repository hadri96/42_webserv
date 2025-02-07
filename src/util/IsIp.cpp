#include "IsIp.hpp"
#include "ToInt.hpp"
#include <sstream>

bool isIp(const std::string& ip)
{
    std::stringstream   ss(ip);
    std::string         part;
    int                 count = 0;

    while (std::getline(ss, part, '.')) {
        if (++count > 4)
            return (false);

        if (part.empty()) return false;
        for (size_t i = 0; i < part.size(); ++i)
		{
            if (!std::isdigit(part[i]))
                return (false);
        }

        int num = toInt(part);
        if (num < 0 || num > 255 || (part.size() > 1 && part[0] == '0'))
            return (false);
    }

    return (count == 4);
}