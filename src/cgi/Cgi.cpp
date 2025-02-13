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
#include <fcntl.h>

// =============================================================================
// Constructors and Destructor
// =============================================================================

Cgi::Cgi(void)
{}

Cgi::Cgi(Config& config, HttpRequest& request)
{
	char 	cwd[1024];

	std::cout << getcwd(cwd, sizeof(cwd)) << std::endl;

	Uri                 uri = request.getUri();
	const Path*         phpScript = config.getPath(uri);
	Path				phpScriptPath = *phpScript;
	
	phpScriptPath = phpScriptPath / uri;
	// chdir somewhere here
	
	cgiExecutable_ = Path("/usr/bin/php-cgi");
	cgiScriptPath_ = phpScriptPath.getAbsPath();

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

// Change so that it can send an error code or find a way to generate a 408 status code (Request Timeout)
int    Cgi::runCgi(std::string& output, HttpRequest& request) 
{
	std::string		requestData = request.getBody();
    int             pipe_stdin[2];  
    int             pipe_stdout[2]; 
	std::string		cgiExecutableStr = cgiExecutable_;
	std::string		cgiScriptPathStr = cgiScriptPath_;

    Logger::logger()->log(LOG_DEBUG, "Creating pipes");

    if (pipe(pipe_stdin) == -1 || pipe(pipe_stdout) == -1)
	{
        Logger::logger()->log(LOG_ERROR, "Pipe creation failed");
        return (1);
    }

    Logger::logger()->log(LOG_DEBUG, "Forking process");

    pid_t pid = fork();

    if (pid == -1)
	{
        Logger::logger()->log(LOG_ERROR, "Fork failed");
        return (1);
    }

    if (pid == 0)
	{ 
        Logger::logger()->log(LOG_DEBUG, "In child process, redirecting stdin and stdout");
        
        if (dup2(pipe_stdin[0], STDIN_FILENO) == -1 || dup2(pipe_stdout[1], STDOUT_FILENO) == -1) 
		{
            Logger::logger()->log(LOG_ERROR, "dup2 failed");
            kill(pid, SIGKILL);
        }

        close(pipe_stdin[0]);
        close(pipe_stdin[1]);
        close(pipe_stdout[0]);
        close(pipe_stdout[1]);

		char* 		args[3];
		
		args[0] = const_cast<char*>(cgiExecutableStr.c_str());
		args[1] = const_cast<char*>(cgiScriptPathStr.c_str());
		args[2] = NULL;

		execve(args[0], args, cgiEnv_);
        Logger::logger()->log(LOG_ERROR, "exec failed");
        kill(pid, SIGKILL);
    }
	else
	{ 
        close(pipe_stdin[0]);
        close(pipe_stdout[1]);
        fcntl(pipe_stdout[0], F_SETFL, O_NONBLOCK);

        if (write(pipe_stdin[1], requestData.c_str(), requestData.size()) == -1)
            Logger::logger()->log(LOG_ERROR, "Write to stdin pipe failed");
        
		close(pipe_stdin[1]);

        char 			buffer[4096];
        ssize_t 		bytesRead;
        time_t 			startTime = time(NULL);
        const int 		timeout = 5;

        while (true)
		{
            bytesRead = read(pipe_stdout[0], buffer, sizeof(buffer));
            
            if (bytesRead > 0) 
			{
                output.append(buffer, bytesRead);
                Logger::logger()->log(LOG_DEBUG, "Read " + toString(bytesRead) + " bytes from child process");
            } 
			else if (time(NULL) - startTime > timeout) 
			{
                Logger::logger()->log(LOG_ERROR, "Timeout reading from child process");

                kill(pid, SIGKILL);
				return (2);
                break;
            }
            if (bytesRead == 0)
			{
                Logger::logger()->log(LOG_INFO, "Read all bytes from child process");
                break;
            }
			if (bytesRead < 0)
            {
				// bytesRead < 0 in non-blocking mode isn’t a true error; it just means there’s no data available at that moment.
				// Logger::logger()->log(LOG_DEBUG, "No data available to read in child process (EAGAIN or EWOULDBLOCK)");
				continue;
			}
		}
        close(pipe_stdout[0]);
        waitpid(pid, 0, 0);
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

	env["SCRIPT_FILENAME"] = cgiScriptPath_;
	env["REDIRECT_STATUS"] = "200";
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["SERVER_PROTOCOL"] = "HTTP/1.1";
	env["REQUEST_METHOD"] = httpMethodToString(request.getMethod());
	env["REQUEST_URI"] = request.getUri();
	env["SCRIPT_NAME"] = request.getUri(); 
	env["PATH_INFO"] = "";
	env["SERVER_SOFTWARE"] = "webserv/1.0";

    if (request.getMethod() == GET)
	{
        env["QUERY_STRING"] = request.getQueryString();
    }
	else if (request.getMethod() == POST)
	{
		std::string contentType = request.getHeader("Content-Type");
        env["CONTENT_LENGTH"] = toString(request.getBody().size());
        env["CONTENT_TYPE"] = contentType;
    }

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
	int	i = 0;
	while (cgiEnv_[i])
	{
		delete[] cgiEnv_[i];
		i++;
	}
	delete[] cgiEnv_;
}
