#include <iostream>
#include <iomanip>
#include <ctime>

#include "Logger.hpp"

Logger* Logger::logger_ = 0;


// =============================================================================
// Constructors and Destructor
// =============================================================================

Logger::Logger()
{}

// =============================================================================
// Public Methods
// =============================================================================

Logger*	Logger::logger(void)
{
	if (logger_ == 0)
		logger_ = new Logger();
	return (logger_);
}

void	Logger::log(LogLevel level, const std::string& message) const
{
	int width = 10;
    std::string currentTime = getCurrentTime();

    std::cout << "[" << currentTime << "] ";

	switch(level)
	{
		case LOG_INFO:
			std::cout << std::left << std::setw(width) << "[INFO] " << message << std::endl;
			break ;
		case LOG_ERROR:
			std::cout << std::left << std::setw(width) << "[ERROR] " << message << std::endl;
			break ;
		case LOG_WARNING:
			std::cout << std::left << std::setw(width) << "[WARNING] " << message << std::endl;
			break ;
		default:
			std::cout << std::left << std::setw(width) << "[UNKNOWN] " << message << std::endl;
			break ;
	}
}

// =============================================================================
// Private Methods
// =============================================================================

std::string		Logger::getCurrentTime(void) const
{
	std::time_t currentTime;
	std::tm* 	localTime;
	char		timeBuffer[20];

	currentTime = std::time(0);
	localTime = std::localtime(&currentTime);
	std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
	return (std::string(timeBuffer));
}