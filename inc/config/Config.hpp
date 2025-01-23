#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <ostream>
# include <string>
# include <vector>

# include "ConfigErrorPage.hpp"
# include "ConfigLocation.hpp"
# include "ConfigCgi.hpp"

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

		void							setConfigRedirection(ConfigRedirection redirection);
		ConfigRedirection&				getConfigRedirection(void);

		void							addConfigErrorPage(const ConfigErrorPage& errorPage);
		std::vector<ConfigErrorPage>&	getConfigErrorPages(void);
		const ConfigErrorPage*			getConfigErrorPage(int statusCode) const;

		void							addConfigLocation(const ConfigLocation& location);
		std::vector<ConfigLocation>&	getConfigLocations(void);
						
		bool							checkPathInConfig(Uri& uri, Path& outputPath) const;

		void							log(void);

		// --- RequestInterpreter ---
		bool							isMethodAllowed(HttpMethodType method, Uri uri) const;
		bool							isSizeAllowed(int byteSize, Uri uri) const;

		const Path*						getPath(Uri uri) const;

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
		ConfigErrorPage	getConfigErrorPage(int errorCode);
		*/


	private:
		// --- Private Attributes ---
		std::string						host_;
		int								port_;
		std::string						serverName_;

		std::vector<ConfigErrorPage>	errorPages_;
		ConfigRedirection				redirection_;

		int								clientMaxBodySize_;

		std::vector<ConfigLocation>		locations_;

		// --- Private Methods ---
		
		const ConfigLocation*			getConfigLocation(Uri uri) const;
};

//std::ostream&	operator<<(std::ostream& os, Config& object);

#endif
