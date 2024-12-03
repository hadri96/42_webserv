#ifndef CONFIG_ERROR_PAGE
# define CONFIG_ERROR_PAGE

# include <string>

# include "Path.hpp"

class	ErrorPage
{
	public:
		// --- Constructors and Destructor ---
					ErrorPage(void);
					ErrorPage(const ErrorPage& other);

					ErrorPage(int errorCode, const Path& errorPage);

					~ErrorPage(void);

		// --- Operators Overload ---
		ErrorPage&	operator=(const ErrorPage& rhs);

		// --- Setters and Getters ---
		int			getErrorCode(void) const;
		const Path&	getErrorPage(void) const;

	private:
		// --- Private Attributes ---
		int			errorCode_;
		Path		errorPage_;
};

#endif
