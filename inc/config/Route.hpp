#ifndef ROUTE_HPP
# define ROUTE_HPP

# include <vector>

# include "HttpMethodType.hpp"
# include "HttpRedirection.hpp"

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
		std::vector<HttpMethodType>	allowedMethods_;
		HttpRedirection				httpRedirection_;
		Path						routePath_;
		bool						autoIndex_;
		Path						defaultFile_;
		Path						uploadDirectory_;

};

#endif
