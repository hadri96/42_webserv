#ifndef CONFIG_ERROR_PAGE
# define CONFIG_ERROR_PAGE

# include <string>

# include "Path.hpp"

class	ErrorPage
{
	private:
		int			error_;
		Path		path;
};

#endif
