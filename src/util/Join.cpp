#include "Join.hpp"

std::string	join(const std::vector<std::string>& strings, const std::string& separator)
{
	std::string str;
	for (size_t i = 0; i != strings.size(); ++i)
	{
		str.append(strings[i]);
		if (i != strings.size() - 1)
			str.append(separator);
	}
	return (str);	
}