#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#include "Colors.hpp"
#include "Logger.hpp"

Logger* Logger::logger_ = 0;
int		Logger::width_ = 10;

// =============================================================================
// Constructors and Destructor
// =============================================================================

Logger::Logger()
{}

Logger::~Logger()
{}

// =============================================================================
// Public Methods
// =============================================================================

Logger*	Logger::logger(void)
{
	if (logger_ == 0)
	{
		logger_ = new Logger();
	}
		
	return (logger_);
}
// --- Title ---
void	Logger::logTitle(LogLevel level, const std::string& title, int titleLevel) const
{
	std::string decoration;

	int n = 58 + (2 * titleLevel);
	decoration = std::string(n, '-');

	std::cout	<< getColor(level)
				<< getCurrentTime()
				<< std::left << std::setw(width_) << getLevel(level)
				<< decoration
				<< " " << title << " "
				<< RESET
				<< std::endl;
}

void	Logger::logTitle(LogLevel level, const std::ostringstream& oss, int titleLevel, bool reset) const
{
	std::string decoration;

	int n = 58 + (2 * titleLevel);
	decoration = std::string(n, '-');

	std::cout	<< getColor(level)
				<< getCurrentTime()
				<< std::left << std::setw(width_) << getLevel(level)
				<< decoration
				<< " " << oss.str() << " "
				<< RESET
				<< std::endl;

    if (reset)
    {
        const_cast<std::ostringstream&>(oss).str("");
        const_cast<std::ostringstream&>(oss).clear();
    }
}

// --- Message ---
void	Logger::log(LogLevel level, const std::string& message, bool prefix) const
{
	if (!prefix)
	{
		std::cout	<< getColor(level)
			<< message
			<< RESET
			<< std::endl;
	}

	std::cout	<< getColor(level)
				<< getCurrentTime()
				<< std::left << std::setw(width_) << getLevel(level)
				<< message
				<< RESET
				<< std::endl;
}

void	Logger::log(LogLevel level, const std::ostringstream& oss, bool reset) const
{
	std::cout	<< getColor(level)
				<< getCurrentTime()
				<< std::left << std::setw(width_) << getLevel(level)
				<< oss.str();

	if (reset)
    {
        const_cast<std::ostringstream&>(oss).str("");
        const_cast<std::ostringstream&>(oss).clear();
    }

	std::cout	<< RESET
				<< std::endl;
}

// =============================================================================
// Private Methods
// =============================================================================

std::string		Logger::getColor(int level) const
{
	switch(level)
	{
		case LOG_INFO:
			return (C_GRN);
		case LOG_ERROR:
			return (C_RED);
		case LOG_WARNING:
			return (C_MAG);
		case LOG_DEBUG:
			return (C_CYN);
		default:
			return (C_WHT);
	}
}

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
			return ("[INFO]");
		case LOG_ERROR:
			return ("[ERROR]");
		case LOG_WARNING:
			return ("[WARNING]");
		case LOG_DEBUG:
			return ("[DEBUG]");
		default:
			return ("[UNKNOWN]");
	}
}

void	Logger::destroy(void)
{
	std::cout << "Logger : destroy method called" << std::endl;
	if (logger_)
	{
		delete logger_;
	logger_ = 0;
	}
}