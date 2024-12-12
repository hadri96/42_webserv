#include <iostream>
#include <iomanip>
#include <ctime>

#include "Logger.hpp"

Logger* Logger::logger_ = 0;
int		Logger::width_ = 10;

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
	std::cout	<< getCurrentTime() 
				<< std::left << std::setw(width_) << getLevel(level) 
				<< message << std::endl;
}

void	Logger::log(LogLevel level, const std::ostringstream& oss) const
{
	std::cout	<< getCurrentTime() 
				<< std::left << std::setw(width_) << getLevel(level) 
				<< oss.str() << std::endl;
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
	return ("[" + std::string(timeBuffer) + "] ");
}

std::string	Logger::getLevel(LogLevel level) const
{
	switch(level)
	{
		case LOG_INFO:
			return ("\033[32m[INFO]\033[0m ");
		case LOG_ERROR:
			return ("\033[31m[ERROR]\033[0m ");
		case LOG_WARNING:
			return ("\033[35m[WARNING]\033[0m ");
		case LOG_DEBUG:
			return ("\033[34m[DEBUG]\033[0m "); 
		default:
			return ("\033[0m[UNKNOWN] "); 
	}	
}