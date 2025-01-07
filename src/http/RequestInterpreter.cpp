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

void    RequestInterpreter::interpret(HttpRequest& request, Config& config)
{
    HttpMethodType      method = request.getMethod();
    
    if (!isAllowedMethod(config))
        Logger::logger()->log(LOG_ERROR, "Method not allowed by server");
    if (config.getClientMaxBodySize() < request.getBodySize())
        Logger::logger()->log(LOG_ERROR, "Request Body Size Exceeded");

    switch (method)
    {
        case GET:
            Logger::logger()->log(LOG_INFO, "CLient sent a GET request");
            handleGetRequest(config, request);
            break;
        case POST:
            Logger::logger()->log(LOG_INFO, "CLient sent a POST request");
            // get request content length header (if too big --> 403)
            handlePostRequest(config, request);
            break;
        case DELETE:
            Logger::logger()->log(LOG_INFO, "CLient sent a DELETE request");
            handleDeleteRequest(config, request);
            break;
        case UNDEFINED:
            throw (RequestInterpreter::BadRequest());
    }
}

// =============================================================================
// Private Methods 
// =============================================================================

// Check if method is allowed by the config file
bool    RequestInterpreter::isAllowedMethod(Config& config)
{
    (void)config;
    // implementation here
    return (true);
}

void    RequestInterpreter::handleGetRequest(Config& config, HttpRequest& request)
{
    Uri     uri = request.getRelativeUri(); // "/index.html"
    Path    configPath = config.getPathFromUri(uri); // "www/html/"
    Path    newPath = configPath.addUri(uri); // "www/html/index.html"

    Logger::logger()->log(LOG_INFO, "relative Uri: " + uri.getUri());
    Logger::logger()->log(LOG_INFO, "newPath: " + newPath.getPath());

    // check if resource exists within server -->

    // check if redirection 
    // get filepath or redirection path
    // check if directory or file 
        // if directory get index file
        // check if directory listing is on
    // build File object
    // check permissions
    // build HttpResponse with 200 OK
}

void    RequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
{
    Uri     uri = request.getRelativeUri();

    Logger::logger()->log(LOG_INFO, config.getServerName());
    // check if resource exists
    // check if resource is allowed
    // get request content length header (check not too big --> 403)

}

void    RequestInterpreter::handleDeleteRequest(Config& config, HttpRequest& request)
{
    Uri     uri = request.getRelativeUri();

    Logger::logger()->log(LOG_INFO, config.getServerName());
}