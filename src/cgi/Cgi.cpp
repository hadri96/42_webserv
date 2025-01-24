#include "Cgi.hpp"
#include "Logger.hpp"
#include "ToString.hpp"

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <iostream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Cgi::Cgi(void) {}

Cgi::Cgi(Config& config, HttpRequest& request)
{
    char 	cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        cgiExecutable_ = std::string(cwd) + "/www/cgi-bin/hello.php";
    else
        Logger::logger()->log(LOG_ERROR, "Unable to get current working directory (cwd for CGI)");
    cgiScriptPath_ = "/usr/bin/php"; 
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

int    Cgi::runCgi()
{
    char*       args[3];

    args[0] = const_cast<char*>(cgiScriptPath_.c_str());
    args[1] = const_cast<char*>(cgiExecutable_.c_str());
    args[2] = NULL;

    pid_t       pid = fork();

    if (pid < 0)
    {
        Logger::logger()->log(LOG_ERROR, "Error in fork() function");
        freeCgiEnv();
        return (-1);
    }
    else if (pid == 0)
    {
        Logger::logger()->log(LOG_DEBUG, "cgiExecutable : " + cgiExecutable_);
        Logger::logger()->log(LOG_DEBUG, "cgiScriptPath : " + cgiScriptPath_);
        if (execve(cgiExecutable_.c_str(), args, cgiEnv_) == -1)
        {
            Logger::logger()->log(LOG_ERROR, "Execve failed in child process");
            freeCgiEnv();
            exit(1);
        }
    }
    else
    {
        int     status;

        if (waitpid(pid, &status, 0) == -1) 
        {
            Logger::logger()->log(LOG_ERROR, "Problem waiting for the Cgi Process");
            freeCgiEnv();
            return (-1);
        }
    }
    return (0);
}

// =============================================================================
// Private Methods
// =============================================================================


void    Cgi::prepareCgiEnvironment(Config& config, HttpRequest& request)
{
    std::map<std::string, std::string>      env;

    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["REQUEST_METHOD"] = HttpMethodTypeToString(request.getMethod());
    env["SCRIPT_FILENAME"] = request.getUri();
    env["PATH_INFO"] = *config.getPath(request.getUri());
    env["NAME"] = request.getInput("name");
    env["CONTENT"] = request.getInput("content");

    cgiEnv_ = new char*[env.size() + 1];

    size_t      i = 0;

    for (std::map<std::string, std::string>::const_iterator it = env.begin(); it != env.end(); ++it) 
    {
        std::string entry = it->first + "=" + it->second;

        cgiEnv_[i] = new char[entry.size() + 1];
        std::strcpy(cgiEnv_[i], entry.c_str());
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
