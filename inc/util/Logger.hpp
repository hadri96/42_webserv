#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>
# include <sstream> // std::ostringstream

enum	LogLevel
{
	LOG_INFO,
	LOG_ERROR,
	LOG_WARNING,
	LOG_DEBUG
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
		static int		width_;

		// --- Private Methods ---
		std::string		getCurrentTime(void) const;
		std::string		getLevel(LogLevel level) const;
		std::string		getColor(int level) const;

	public:
		// --- Public Methods ---
		static Logger*	logger(void);
		void			logTitle(LogLevel level, const std::string& title, int titleLevel = 1) const;
		void			logTitle(LogLevel level, const std::ostringstream& oss, int titleLevel = 1) const;

		void			log(LogLevel level, const std::string& message) const;
		void			log(LogLevel level, const std::ostringstream& oss, bool reset = true) const;
		// void			logStream(std::stringstream ss);
};

#endif
