#include "Cgi.hpp"
#include "Logger.hpp"
#include "ToString.hpp"
#include "HttpMethodType.hpp"

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Cgi::Cgi(void)
{}

Cgi::Cgi(Config& config, HttpRequest& request)
{
    char 	cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        cgiExecutable_ = std::string(cwd) + "/www/cgi-bin/hello.php";
    else
        Logger::logger()->log(LOG_ERROR, "Unable to get current working directory (cwd for CGI)");
    
    cgiScriptPath_ = "/usr/bin/php-cgi"; // php-cgi and not php
    //cgiScriptPath_ = "/run/current-system/sw/bin/php-cgi";
    
    prepareCgiEnvironment(config, request);
}

Cgi::~Cgi() 
{
    if (cgiEnv_)
        freeCgiEnv();
}

// =============================================================================
// Public Methods
// =============================================================================

int    Cgi::runCgi(std::string& output)
{
    int         pipeFd[2];

    if (pipe(pipeFd) == -1)
    {
        Logger::logger()->log(LOG_ERROR, "Error creating pipe");
        return (-1);
    }

    pid_t       pid = fork();

    if (pid < 0)
    {
        Logger::logger()->log(LOG_ERROR, "Error in fork() function");
        freeCgiEnv();
        return (-1);
    }
    else if (pid == 0)
    {
        close(pipeFd[0]);
        dup2(pipeFd[1], STDOUT_FILENO);
        close(pipeFd[1]);

        char*       args[3];

        args[0] = const_cast<char*>(cgiScriptPath_.c_str());
        args[1] = const_cast<char*>(cgiExecutable_.c_str());
        args[2] = NULL;
        
        if (execve(args[0], args, cgiEnv_) == -1)
        {
            Logger::logger()->log(LOG_ERROR, "Execve failed in child process");
            freeCgiEnv();
            exit(1);
        }
    }
    else
    {
        close(pipeFd[1]);

        char        buffer[1024];
        ssize_t     bytesRead;
        
        output.clear();

        while ((bytesRead = read(pipeFd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytesRead] = '\0';
            output += buffer;
        }

        close(pipeFd[0]);
        waitpid(pid, NULL, 0);
    }
    return (0);
}

// =============================================================================
// Private Methods
// =============================================================================


void    Cgi::prepareCgiEnvironment(Config& config, HttpRequest& request)
{
    std::map<std::string, std::string>      env;

    (void) config;

    // Absolute path to script
    env["SCRIPT_FILENAME"] = cgiExecutable_; // Use full filesystem path
    
    // Required for PHP-CGI security check
    env["REDIRECT_STATUS"] = "200";
    
    // Standard CGI variables
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["REQUEST_METHOD"] = httpMethodToString(request.getMethod());
    env["QUERY_STRING"] = request.getQueryString();
    
    // URL-related variables
    env["REQUEST_URI"] = request.getUri();
    env["SCRIPT_NAME"] = request.getUri(); // URL path to script
    env["PATH_INFO"] = ""; // Empty unless using path-based routing

    // Server information
    env["SERVER_SOFTWARE"] = "webserv/1.0";

    cgiEnv_ = new char*[env.size() + 1];

    size_t      i = 0;

    for (std::map<std::string, std::string>::const_iterator it = env.begin(); it != env.end(); ++it) 
    {
        std::string entry = it->first + "=" + it->second;

        cgiEnv_[i] = new char[entry.size() + 1];
        std::strcpy(cgiEnv_[i], entry.c_str());
        Logger::logger()->log(LOG_DEBUG, "cgiEnv[" + toString(i) + "] : " + cgiEnv_[i]);
        i++;
    }
    cgiEnv_[i] = NULL;
}

void    Cgi::freeCgiEnv()
{
    int     i = 0;
    while (cgiEnv_[i])
    {
        delete (cgiEnv_[i++]);
    }
    delete (cgiEnv_);
}
