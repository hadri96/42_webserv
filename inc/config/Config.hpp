#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <ostream>
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
		const std::string&				getHost(void) const;

		void							setPort(int port);
		int								getPort(void) const;

		void							setServerName(const std::string& serverName);
		const std::string&				getServerName(void) const;

		void							setClientMaxBodySize(int clientMaxBodySize);
		int								getClientMaxBodySize(void) const;

		void							setHttpRedirection(HttpRedirection redirection);
		HttpRedirection&				getHttpRedirection(void);

		void							addErrorPage(const ErrorPage& errorPage);
		void							addRoute(const Route& route);

		std::vector<ErrorPage>&			getErrorPages(void);
		std::vector<Route>&				getRoutes(void);
		const ErrorPage					getErrorPage(int statusCode);							
		const Path&						getPathFromUri(Uri& uri) const;
		
		const Route&					getRoute(Uri uri);

		void							log(void);

		/*
		Methodes necessaires pour Interpreter:

		bool		isAllowedMethod(HttpMethodType& method);
		bool		isRedirection(Uri& uri);
		Path&		getRedirection(Uri& uri);
		{
			gets redirection if there is one
			if not gets path (in server) from uri
		}
		bool		hasReadPermissions(File& file);
		bool		isDirectory(Uri& uri);
		bool		directoryListing();
		File		getIndexFile();
		ErrorPage	getErrorPage(int errorCode);
		*/


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

//std::ostream&	operator<<(std::ostream& os, Config& object);

#endif
