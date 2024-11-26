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

					~ErrorPage(void);

		// --- Operators Overload ---
		ErrorPage&	operator=(const ErrorPage& rhs);

	private:
		// --- Private Attributes ---
		int			error_;
		Path		path_;
};

#endif
