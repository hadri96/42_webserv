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

	std::cout << getcwd(cwd, sizeof(cwd)) << std::endl;

	Uri                 uri = request.getUri();
	const Path*         phpScript = config.getPath(uri);
	Path				phpScriptPath = *phpScript;
	
	phpScriptPath = phpScriptPath / uri;
	cgiExecutable_ = phpScriptPath.getAbsPath();

	//cgiExecutable_ = Path("/www/cgi-bin/hello.php").getAbsPath();
	
	cgiScriptPath_ = Path("/usr/bin/php-cgi"); // php-cgi and not php
	//cgiScriptPath_ = Path("/run/current-system/sw/bin/php-cgi");

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

/*int    Cgi::runCgi(std::string& output, HttpRequest& request)
{
	int         stdinPipe[2];
	int         stdoutPipe[2];
	pid_t       pid;
	char        buffer[1024];
	ssize_t     bytesRead;

	std::string	cgiExecutableStr = cgiExecutable_;
	std::string	cgiScriptPathStr = cgiScriptPath_;

	if (pipe(stdinPipe) == -1 || pipe(stdoutPipe) == -1)
	{
		Logger::logger()->log(LOG_ERROR, "Error creating pipes");
		return (-1);
	}

	pid = fork();
	if (pid < 0)
	{
		Logger::logger()->log(LOG_ERROR, "Error in fork()");
		close(stdinPipe[0]); close(stdinPipe[1]);
		close(stdoutPipe[0]); close(stdoutPipe[1]);
		return (-1);
	}
	else if (pid == 0) // Child process
	{
		close(stdinPipe[1]);   // Close write end of stdin pipe
		close(stdoutPipe[0]);  // Close read end of stdout pipe

		// Redirect stdin to read from the stdin pipe
		if (dup2(stdinPipe[0], STDIN_FILENO) == -1) {
			Logger::logger()->log(LOG_ERROR, "dup2 stdin failed");
			exit(1);
		}
		close(stdinPipe[0]);

		// Redirect stdout to write to the stdout pipe
		if (dup2(stdoutPipe[1], STDOUT_FILENO) == -1) {
			Logger::logger()->log(LOG_ERROR, "dup2 stdout failed");
			exit(1);
		}
		close(stdoutPipe[1]);

		// Execute PHP script
		char* args[3];
		args[0] = const_cast<char*>(cgiScriptPathStr.c_str());
		args[1] = const_cast<char*>(cgiExecutableStr.c_str());
		args[2] = NULL;

		execve(args[0], args, cgiEnv_);
		Logger::logger()->log(LOG_ERROR, "Execve failed");
		exit(1);
	}
	else // Parent process
	{
		close(stdinPipe[0]);   // Close read end of stdin pipe
		close(stdoutPipe[1]);  // Close write end of stdout pipe

		// Write POST data to stdin pipe
		if (request.getMethod() == POST)
		{
			const std::string& postData = request.getBody();
			write(stdinPipe[1], postData.c_str(), postData.size());
		}
		close(stdinPipe[1]);  // Close after writing to signal EOF

		// Read output from stdout pipe
		output.clear();
		while ((bytesRead = read(stdoutPipe[0], buffer, sizeof(buffer)-1)) > 0)
		{
			buffer[bytesRead] = '\0';
			output += buffer;
		}
		close(stdoutPipe[0]);

		waitpid(pid, NULL, 0);  // Wait for child to exit
	}
	return (0);
}*/

int    Cgi::runCgi(std::string& output, HttpRequest& request) 
{
    //std::string     requestData = request.getRawRequest(); // Full http request (header, body, everything)
	std::string		requestData = request.getBody(); // Just the body

    int             pipe_stdin[2];  // Pipe for sending data to php-cgi's stdin
    int             pipe_stdout[2]; // Pipe for receiving data from php-cgi's stdout

	std::string		cgiExecutableStr = cgiExecutable_;
	std::string		cgiScriptPathStr = cgiScriptPath_;

    Logger::logger()->log(LOG_DEBUG, "Creating pipes");

    // Create pipes
    if (pipe(pipe_stdin) == -1 || pipe(pipe_stdout) == -1){
        Logger::logger()->log(LOG_ERROR, "Pipe creation failed");
        throw std::runtime_error("pipe");
    }

    Logger::logger()->log(LOG_DEBUG, "Forking process");

    // Fork the process
    pid_t pid = fork();

    if (pid == -1)
	{
        Logger::logger()->log(LOG_ERROR, "Fork failed");
        throw std::runtime_error("fork");
    }

    if (pid == 0) // --- Child process (php-cgi) ---
	{ 
        Logger::logger()->log(LOG_DEBUG, "In child process, redirecting stdin and stdout");
        Logger::logger()->log(LOG_DEBUG, "pipe_stdin[0]:" + toString(pipe_stdin[0]));
        Logger::logger()->log(LOG_DEBUG, "pipe_stdout[1]: " + toString(pipe_stdout[1]));

        // Redirect stdin and stdout
        if (dup2(pipe_stdin[0], STDIN_FILENO) == -1) {
            Logger::logger()->log(LOG_ERROR, "dup2 stdin failed");
            exit(1);
        }
        if (dup2(pipe_stdout[1], STDOUT_FILENO) == -1) {
            Logger::logger()->log(LOG_ERROR, "dup2 stdout failed");
            exit(1);
        }

        // Close unused pipe ends
        close(pipe_stdin[0]);
        close(pipe_stdin[1]);
        close(pipe_stdout[0]);
        close(pipe_stdout[1]);

        Logger::logger()->log(LOG_DEBUG, "Executing php-cgi");
        
		// Execute php-cgi
		char* args[3];
		args[0] = const_cast<char*>(cgiScriptPathStr.c_str());
		args[1] = const_cast<char*>(cgiExecutableStr.c_str());
		args[2] = NULL;

		execve(args[0], args, cgiEnv_);
        Logger::logger()->log(LOG_ERROR, "exec failed");
        exit(1);
    }
	else // --- Parent process (webserv) ---
	{ 
		Logger::logger()->log(LOG_DEBUG, "pipe_stdin[1]:" + toString(pipe_stdin[1]));
        Logger::logger()->log(LOG_DEBUG, "pipe_stdout[0]: " + toString(pipe_stdout[0]));
        
        // Close unused pipe ends
        close(pipe_stdin[0]);
        close(pipe_stdout[1]);

        Logger::logger()->log(LOG_DEBUG, "Writing request data to child process: " + requestData);
        
		// Write the request data to php-cgi's stdin
        if (write(pipe_stdin[1], requestData.c_str(), requestData.size()) == -1)
            Logger::logger()->log(LOG_ERROR, "Write to stdin pipe failed");
        
		close(pipe_stdin[1]); // Close stdin to signal end of input

        Logger::logger()->log(LOG_DEBUG, "Reading response from child process");
        // Read the response from php-cgi's stdout
        char buffer[4096];
        ssize_t bytes_read;

        while ((bytes_read = read(pipe_stdout[0], buffer, sizeof(buffer))) > 0)
		{
            Logger::logger()->log(LOG_DEBUG, "Read" +  toString(bytes_read) + " bytes from child process");
            output.append(buffer, bytes_read);
        }

        close(pipe_stdout[0]);

        Logger::logger()->log(LOG_DEBUG, "Waiting for child process to finish");
        // Wait for the php-cgi process to finish
        waitpid(pid, 0, 0);

        Logger::logger()->log(LOG_DEBUG, "Final output size: " + toString(output.size()) + " bytes");
        Logger::logger()->log(LOG_DEBUG, "Sending response to client");
        std::cout << output << std::endl;
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
	
	// URL-related variables
	env["REQUEST_URI"] = request.getUri();
	env["SCRIPT_NAME"] = request.getUri(); // URL path to script
	env["PATH_INFO"] = ""; // Empty unless using path-based routing

	// Server information
	env["SERVER_SOFTWARE"] = "webserv/1.0";

	
	// Add CONTENT_LENGTH and CONTENT_TYPE for POST requests


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

	/*
	if (request.getMethod() == POST)
	{
		env["CONTENT_LENGTH"] = toString(request.getBody().size());
		std::string contentType = request.getHeader("Content-Type");
		if (!contentType.empty())
			env["CONTENT_TYPE"] = contentType;
		else
			env["CONTENT_TYPE"] = "application/x-www-form-urlencoded"; // Default
	}
	*/

	/*if (request.getMethod() == POST)
	{
		env["CONTENT_LENGTH"] = toString(request.getBody().size());
    	std::string contentType = request.getHeader("Content-Type");
		if (contentType.find("multipart/form-data") != std::string::npos)
		{
			env["CONTENT_TYPE"] = "multipart/form-data";
		} 
		else
		{
			env["CONTENT_TYPE"] = contentType.empty() ? "application/x-www-form-urlencoded" : contentType;
		}
	}*/


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
		delete (cgiEnv_[i++]);
	}
	delete (cgiEnv_);
}
