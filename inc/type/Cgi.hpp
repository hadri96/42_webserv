#ifndef CGI_HPP
# define CGI_HPP

# include "Config.hpp"
# include "HttpRequest.hpp"

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
        int             runCgi();

    private:
    	// --- Private Attributes ---
        char**          cgiEnv_;
        std::string     cgiScriptPath_;
        std::string     cgiExecutable_;


    	// --- Private Methods ---
        void            prepareCgiEnvironment(Config& config, HttpRequest& request);
        void            freeCgiEnv();

};

#endif
