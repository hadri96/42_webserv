#ifndef CGI_HPP
# define CGI_HPP

# include "Config.hpp"
# include "HttpRequest.hpp"
# include "Path.hpp"

# include <string>
# include <map>

class Cgi 
{
	public:
		// --- Constructors and Destructor ---
						Cgi();
						Cgi(Config& config, HttpRequest& request);
						~Cgi();

		// --- Public Methods ---
		Resource*		runCgi(HttpRequest& request, Config& config);

	private:
		// --- Private Attributes ---
		char**			cgiEnv_;
		Path			cgiScriptPath_;
		Path			cgiExecutable_;

		// --- Private Methods ---
		void			prepareCgiEnvironment(Config& config, HttpRequest& request);
		void			freeCgiEnv();
		std::string		urlDecode(const std::string& encoded);
};

#endif
