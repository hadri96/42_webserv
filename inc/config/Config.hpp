#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <vector>

# include "ErrorPage.hpp"
# include "Route.hpp"
# include "Cgi.hpp"

class	Config
{
	private:
		std::string						host_;
		int								port_;
		std::string						serverName_;

		std::vector<ErrorPage>			errorPages_;

		int								clientMaxBodySize_;

		std::vector<Route>				routes_;

		Cgi								cgi_;

};

#endif
