#include "RequestInterpreter.hpp"
#include "ToString.hpp"
#include "HttpMethodType.hpp"
#include "Logger.hpp"

#include <string>
#include <stdexcept>
#include <sys/stat.h> // For struct stat and stat()
#include <unistd.h>   // For realpath()
#include <limits.h>   // For PATH_MAX

// =============================================================================
// Constructors and Destructor
// =============================================================================

RequestInterpreter::RequestInterpreter(Server* server) : server_(server){}

RequestInterpreter::~RequestInterpreter() {}

// =============================================================================
// Getters
// =============================================================================




// =============================================================================
// Public Methods 
// =============================================================================


void    RequestInterpreter::interpret(HttpRequest& request)
{
    // Check Request Method
    HttpMethodType      method = request.getRequestLine().getMethod();

    switch (method)
    {
        case GET:
            Logger::logger()->log(LOG_INFO, "CLient sent a GET request");
            if (fileInServer(request.getRequestLine().getRequestTarget().getPath()))
                Logger::logger()->log(LOG_INFO, "Static file request");
            else // is not a static file request
                Logger::logger()->log(LOG_INFO, "Not a static file request");
            break;
        case POST:
            Logger::logger()->log(LOG_INFO, "CLient sent a POST request");
            break;
        case DELETE:
            Logger::logger()->log(LOG_INFO, "CLient sent a DELETE request");
            break;
        case UNDEFINED:
            throw (RequestInterpreter::BadRequest());
    }
}

// =============================================================================
// Private Methods 
// =============================================================================

// Check if file is in server directory
bool    RequestInterpreter::fileInServer(std::string uri)
{
    if (uri.size() > 0)
        return (true);
    return (false);
}

/*
bool RequestInterpreter::fileInServer(const std::string& uri, const Config& config)
{
    // Combine root directory with the URI
    std::string fullPath = config.rootDirectory + uri;

    // Buffer to store the canonical path
    char resolvedRoot[PATH_MAX];
    char resolvedPath[PATH_MAX];

    // Get canonical path for the root directory
    if (!realpath(config.rootDirectory.c_str(), resolvedRoot)) 
    {
        throw std::runtime_error("Failed to resolve root directory path");
    }

    // Get canonical path for the requested file
    if (!realpath(fullPath.c_str(), resolvedPath)) 
    {
        return false; // If path is invalid, the file does not exist
    }

    // Check if the resolved path starts with the resolved root directory
    std::string resolvedRootStr(resolvedRoot);
    std::string resolvedPathStr(resolvedPath);

    if (resolvedPathStr.find(resolvedRootStr) != 0) 
    {
        return false; // Directory traversal attempt detected
    }

    // Check if the file exists and is a regular file
    struct stat fileStat;
    
    if (stat(resolvedPath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) 
    {
        return true; // File exists and is a regular file
    }

    return false; // File does not exist or is not a regular file
}

*/