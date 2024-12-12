#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <vector>

# include "ErrorPage.hpp"
# include "Route.hpp"
# include "Cgi.hpp"

class	Config
{
	public:
		// --- Constructors and Destructor ---
										Config(void);
										Config(const Config& other);

										~Config(void);
		
		// --- Operators Overload ---
		Config&							operator=(const Config& rhs);

		// --- Setters and Getters ---
		void							setHost(const std::string& host);
		void							setPort(int port);
		void							setServerName(const std::string& serverName);
		void							setClientMaxBodySize(int clientMaxBodySize);
		void							setRedirection(const HttpRedirection& redirection);

		void							addErrorPage(const ErrorPage& errorPage);
		void							addRoute(const Route& route);

		const std::string&				getHost(void) const;
		int								getPort(void) const;
		const std::string&				getServerName(void) const;
		int								getClientMaxBodySize(void) const;
		const std::vector<ErrorPage>&	getErrorPages(void) const;
		const Path&						getErrorPage(int statusCode);							
		const std::vector<Route>&		getRoutes(void) const;
		const Route&					getRoute(Uri uri);

		// const Path						getPathFromUri(Uri uri);


	private:
		// --- Private Attributes ---
		std::string						host_;
		int								port_;
		std::string						serverName_;

		std::vector<ErrorPage>			errorPages_;
		HttpRedirection					redirection_;

		int								clientMaxBodySize_;

		std::vector<Route>				routes_;
};

#endif
