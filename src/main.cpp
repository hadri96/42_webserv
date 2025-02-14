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

void signalHandler(int signal) 
{
    std::cout << "\nSignal received: " << signal << ". Cleaning up...\n";

    // Free your allocated memory here.
    // Example: If you have allocated memory dynamically:
    // delete[] myAllocatedMemory;
    
    // Close sockets or other resources if applicable.
    // Example: close(socket_fd);
    
    // Exit the program gracefully.
    std::exit(signal);
}


int	main(int argc, char** argv)
{
	std::signal(SIGINT, signalHandler);  // SIGINT is triggered by Ctrl+C
    std::signal(SIGTERM, signalHandler); // SIGTERM for termination signals

	std::string 	configPath;

	if (argc == 1)
		configPath = "conf/complex.conf";
	else if (argc == 2)
		configPath = argv[1];

	try
	{
		Webserv webserv(configPath);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}
