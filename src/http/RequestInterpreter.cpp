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

RequestInterpreter::RequestInterpreter(Server* server)
    : server_(server)
{}

RequestInterpreter::~RequestInterpreter()
{}

// =============================================================================
// Getters
// =============================================================================


// =============================================================================
// Public Methods 
// =============================================================================

HttpResponse   RequestInterpreter::interpret(HttpRequest& request, Config& config)
{
    HttpMethodType      method = request.getMethod();
    HttpResponse        response;

    if (!isAllowedMethod(config))
        Logger::logger()->log(LOG_ERROR, "Method not allowed by server");
    if (config.getClientMaxBodySize() < request.getBodySize())
        Logger::logger()->log(LOG_ERROR, "Request Body Size Exceeded");

    switch (method)
    {
        case GET:
            Logger::logger()->log(LOG_INFO, "CLient sent a GET request");
            response = handleGetRequest(config, request);
            break;
        case POST:
            Logger::logger()->log(LOG_INFO, "CLient sent a POST request");
            // get request content length header (if too big --> 403)
            response = handlePostRequest(config, request);
            break;
        case DELETE:
            Logger::logger()->log(LOG_INFO, "CLient sent a DELETE request");
            response = handleDeleteRequest(config, request);
            break;
        case UNDEFINED:
            throw (RequestInterpreter::BadRequest());
    }
    return (response);
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


HttpResponse    RequestInterpreter::handleGetRequest(Config& config, HttpRequest& request)
{
    Uri     uri = request.getRelativeUri();
    Path    fullPath;

    (void) config;

    // check if resource exists within server 
    
    /*if (!config.checkPathInConfig(uri, fullPath))
        return (HttpResponse(config.getErrorPage(404)));
    else*/
        //return (HttpResponse(File(fullPath)));

    return (HttpResponse(config.createResourceError(404)));
    

    // check if redirection 
    // get filepath or redirection path
    // check if directory or file 
        // if directory get index file
        // check if directory listing is on
    // build File object
    // check permissions
    // build HttpResponse with 200 OK
}


HttpResponse    RequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri     uri = request.getRelativeUri();

    Logger::logger()->log(LOG_INFO, config.getServerName());
    // check if resource exists
    // check if resource is allowed
    // get request content length header (check not too big --> 403)
    return (response);
}

HttpResponse    RequestInterpreter::handleDeleteRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri             uri = request.getRelativeUri();

    Logger::logger()->log(LOG_INFO, config.getServerName());
    return (response);
}