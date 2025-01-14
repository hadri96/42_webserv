#ifndef CONFIG_ERROR_PAGE
# define CONFIG_ERROR_PAGE

# include <ostream>
# include <string>

# include "Path.hpp"
# include "File.hpp"

class	ErrorPage
{
	public:
		// --- Constructors and Destructor ---
							ErrorPage(void);
							ErrorPage(int errorCode);
							ErrorPage(const ErrorPage& other);

							ErrorPage(int errorCode, const Path& path);

							~ErrorPage(void);

		// --- Operators Overload ---
		ErrorPage&	operator=(const ErrorPage& rhs);

		// --- Setters and Getters ---
		int					getErrorCode(void) const;
		const File&			getErrorFile(void) const;
		const Path			getErrorPath(void) const;
		// --- Public Attributes ---
		const std::string	read(void) const;

	private:
		// --- Private Attributes ---
		int					errorCode_;
		File				errorFile_;

};

std::ostream&	operator<<(std::ostream& os, ErrorPage& object);

#endif
