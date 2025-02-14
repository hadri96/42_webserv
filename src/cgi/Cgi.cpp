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

#include "Resource.hpp"
#include "ResourceDefault.hpp"

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
	
	cgiScriptPath_ = phpScriptPath.getAbsPath();


	cgiExecutable_ = config.getConfigCgi().getExecutable();

	std::cout << "cgi_executable : " << cgiExecutable_ << std::endl;
	std::cout << "cgi_script_path : " << cgiScriptPath_ << std::endl;

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

Resource*    Cgi::runCgi(HttpRequest& request, Config& config) 
{
	(void) config;
	std::string		output;
	std::string		requestData = request.getBody(); // Just the body

	int             pipe_stdin[2];  // Pipe for sending data to php-cgi's stdin
	int             pipe_stdout[2]; // Pipe for receiving data from php-cgi's stdou
	
	std::string		cgiExecutableStr = cgiExecutable_;
	std::string		cgiScriptPathStr = cgiScriptPath_;

	Path				currentDir = currentDir.getAbsPath();

	Path workingDir = cgiScriptPath_.getParent();
	chdir(std::string(workingDir).c_str());

	Logger::logger()->log(LOG_DEBUG, "Creating pipes");

	// Create pipes
	if (pipe(pipe_stdin) == -1 || 
		pipe(pipe_stdout) == -1)
	{
		Logger::logger()->log(LOG_ERROR, "Pipe creation failed");
		throw std::runtime_error("pipe");
	}

	Logger::logger()->log(LOG_DEBUG, "Forking process");

	// Fork the process
	pid_t pid = fork();

	if (pid == -1)
	{
		Logger::logger()->log(LOG_ERROR, "Fork failed");
		return (new Resource(500));
		throw std::runtime_error("fork");
	}

	if (pid == 0) // --- Child process (php-cgi) ---
	{ 
		Logger::logger()->log(LOG_DEBUG, "In child process, redirecting stdin and stdout");

		// Redirect stdin and stdout
		if (dup2(pipe_stdin[0], STDIN_FILENO) == -1)
		{
			Logger::logger()->log(LOG_ERROR, "dup2 stdin failed");
			return (new Resource(500));
		}

		if (dup2(pipe_stdout[1], STDOUT_FILENO) == -1)
		{
			Logger::logger()->log(LOG_ERROR, "dup2 stdout failed");
			return (new Resource(500));
		}

		// Close unused pipe ends
		close(pipe_stdin[0]);
		close(pipe_stdin[1]);
		close(pipe_stdout[0]);
		close(pipe_stdout[1]);
		
		// Execute php-cgi with extra parameters specified in config file 
		// Step 1: Split the string by whitespaces
		std::vector<std::string> 	argsVec;
		std::string 				parameters = config.getConfigCgi().getParameters();
		std::istringstream 			stream(parameters);
		std::string 				word;
		
		while (stream >> word) 
		{
			argsVec.push_back(word);  // Store each word (argument)
		}

		// Step 2: Count the number of arguments (we add 3 for the executable, script path and NULL)
		size_t count_of_args = argsVec.size() + 3;

		// Step 3: Allocate memory for the arguments array
		char* args[count_of_args];
		
		// Add the executable path
		args[0] = const_cast<char*>(cgiExecutableStr.c_str());

		// Add the arguments from the split string
		for (size_t i = 0; i != argsVec.size(); ++i)
		{
			args[i + 1] = const_cast<char*>(argsVec[i].c_str());
		}

		// Add the script path as the second to last argument
		args[count_of_args - 2] = const_cast<char*>(cgiScriptPathStr.c_str());

		// Null-terminate the arguments array
		args[count_of_args - 1] = NULL;

		// Debugging output: printing the arguments
		for (size_t i = 0; i < count_of_args; ++i) 
		{
			std::cout << "args[" << i << "]: " << args[i] << std::endl;
		}

		execve(args[0], args, cgiEnv_);
		Logger::logger()->log(LOG_ERROR, "exec failed");
		return (new Resource(500));
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
			Logger::logger()->log(LOG_DEBUG, "Read " +  toString(bytes_read) + " bytes from child process");
			output.append(buffer, bytes_read);
		}

		close(pipe_stdout[0]);

		Logger::logger()->log(LOG_DEBUG, "Waiting for child process to finish");
		waitpid(pid, 0, 0);

		Logger::logger()->log(LOG_DEBUG, "Final output size: " + toString(output.size()) + " bytes");
		Logger::logger()->log(LOG_DEBUG, "Sending response to client");

		std::string outputHeaders = output.substr(0, output.find("\r\n\r\n"));
		std::cout << "headers : " << outputHeaders << std::endl;
	}

	std::string outputBody = output.substr(output.find("\r\n\r\n") + 4);
	chdir(std::string(currentDir).c_str());
	return (new Resource(200, outputBody));
}


// =============================================================================
// Private Methods
// =============================================================================

void    Cgi::prepareCgiEnvironment(Config& config, HttpRequest& request)
{
	std::map<std::string, std::string>      env;

	(void) config;

	// Absolute path to script
	env["SCRIPT_FILENAME"] = cgiScriptPath_; // Use full filesystem path
	
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