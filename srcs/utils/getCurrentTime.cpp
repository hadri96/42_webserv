#include "webserv.hpp"

std::string getCurrentTime()
{
	std::time_t rawTime;
	std::tm *timeInfo;
	char buffer[80];

	std::time(&rawTime);				 // Get the current time
	timeInfo = std::localtime(&rawTime); // Convert to local time

	// Format the time as a string
	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
	return std::string(buffer);
}
