#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>

enum	LogLevel
{
	LOG_INFO,
	LOG_ERROR,
	LOG_WARNING
};

class	Logger
{
	private:
		// --- Constructors and Destructor ---
						Logger(void);
						Logger(const Logger&);

						~Logger(void);
		
		// --- Operators Overload ---
		Logger&			operator=(const Logger&);

		// --- Private Attributes ---
		static Logger*	logger_;

		// --- Private Methods ---
		std::string		getCurrentTime(void) const;

	public:
		// --- Public Methods ---
		static Logger*	logger(void);
		void			log(LogLevel level, const std::string& message) const;
		// void			logStream(std::stringstream ss);
};

#endif
