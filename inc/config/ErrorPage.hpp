#ifndef CONFIG_ERROR_PAGE
# define CONFIG_ERROR_PAGE

# include <ostream>
# include <string>

# include "Uri.hpp"

class	ErrorPage
{
	public:
		// --- Constructors and Destructor ---
							ErrorPage(void);
							ErrorPage(const ErrorPage& other);

							ErrorPage(int errorCode, Uri uri);

							~ErrorPage(void);

		// --- Operators Overload ---
		ErrorPage&			operator=(const ErrorPage& rhs);
		bool				operator==(int code) const;

		// --- Setters and Getters ---
		int					getCode(void) const;
		Uri					getUri(void) const;

		// --- Public Attributes ---
		void				display(void);

	private:
		// --- Private Attributes ---
		int					code_;
		Uri					uri_;

};

#endif