#ifndef ROUTE_HPP
# define ROUTE_HPP

# include <vector>

# include "HttpMethodType.hpp"
# include "HttpRedirection.hpp"

class	Route
{
	private:
		std::vector<HttpMethodType>	allowedMethods_;
		HttpRedirection				httpRedirection_;
		Path						routePath_;
		bool						autoIndex_;
		Path						defaultFile_;
		Path						uploadDirectory_;

};

#endif