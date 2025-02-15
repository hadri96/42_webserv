#include "Webserv.hpp"
#include "Observer.hpp"
#include "Server.hpp"
#include "Logger.hpp"
#include "Config.hpp"

#include <iostream>

#include "PathOrUri.hpp"
#include "Path.hpp"

#include "HttpMimeTypes.hpp"
#include "ToVector.hpp"
#include <csignal>  // For signal handling
#include <cstdlib>  // For exit()

// Global variable to track the status
int gMustStop = 0;

// Signal handler for SIGINT (Ctrl+C)
void handleSigInt(int sig)
{
	std::cout << "Stopping the server..." << std::endl;
	(void) sig;
	gMustStop = 1;
}

// Signal handler for SIGQUIT (Ctrl+D or other quit signal)
void handleSigQuit(int sig)
{
	std::cout << "Stopping the server..." << std::endl;
	(void) sig;
	gMustStop = 1;
}

int	main(int argc, char** argv)
{
	// Set signal handlers
    signal(SIGINT, handleSigInt);   // Handle Ctrl+C
    signal(SIGQUIT, handleSigQuit); // Handle Ctrl+D

	std::string 	configPath;

	if (argc == 1)
		configPath = "conf/complex.conf";
	else if (argc == 2)
		configPath = argv[1];

	try
	{
		Webserv webserv(configPath);
		Logger::destroy();
		std::cout << "--- Position : end of main ---" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
