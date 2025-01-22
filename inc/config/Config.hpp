#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <ostream>
# include <string>
# include <vector>

# include "ErrorPage.hpp"
# include "Location.hpp"
# include "Cgi.hpp"

# include "Resource.hpp"

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
		void							addLocation(const Location& Location);

		std::vector<ErrorPage>&			getErrorPages(void);
		std::vector<Location>&			getLocations(void);
						
		bool							checkPathInConfig(Uri& uri, Path& outputPath) const;

		void							log(void);

		// --- RequestInterpreter ---
		bool							isMethodAllowed(HttpMethodType method, Uri uri) const;
		bool							isSizeAllowed(int byteSize, Uri uri) const;

		// --- Resources ---
		Resource						createResourceFile(Uri uri);
		Resource						createResourceError(int code);
		Resource						createResourceDirectoryList(Path path);


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

		std::vector<Location>			locations_;

		// --- Private Methods ---
		const Path*						getPath(Uri uri) const;
		const Location*					getLocation(Uri uri) const;
		const ErrorPage*				getErrorPage(int statusCode) const;
};

//std::ostream&	operator<<(std::ostream& os, Config& object);

#endif
