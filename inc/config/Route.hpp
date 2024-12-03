#ifndef ROUTE_HPP
# define ROUTE_HPP

# include <vector>

# include "HttpMethodType.hpp"
# include "HttpRedirection.hpp"
# include "Uri.hpp"

class	Route
{
	public:
	// --- Constructors and Destructor ---
									Route(void);
									Route(const Route& other);

									~Route(void);

	// --- Operators Overload ---
	Route&							operator=(const Route& rhs);

	private:
		// --- Private Attributes ---
		Uri							uri_;
		Path						rootPath_;

		std::vector<HttpMethodType>	allowedMethods_;

		HttpRedirection				redirection_;
		
		bool						autoIndex_;
		Path						defaultFile_;
		Path						uploadDirectory_;

		// Cgi							cgi_;
};

#endif
