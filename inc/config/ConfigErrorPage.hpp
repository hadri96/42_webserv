#ifndef CONFIG_ERROR_PAGE
# define CONFIG_ERROR_PAGE

# include <ostream>
# include <string>

# include "Uri.hpp"

class	ConfigErrorPage
{
	public:
		// --- Constructors and Destructor ---
							ConfigErrorPage(void);
							ConfigErrorPage(const ConfigErrorPage& other);

							ConfigErrorPage(int errorCode, Uri uri);

							~ConfigErrorPage(void);

		// --- Operators Overload ---
		ConfigErrorPage&	operator=(const ConfigErrorPage& rhs);
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