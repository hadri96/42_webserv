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
    HttpMethodType      method = request.getRequestLine().getMethod();

    if (!isAllowedMethod(config))
    {
        Logger::logger()->log(LOG_ERROR, "Method not allowed by server");
    }

    switch (method)
    {
        case GET:
            Logger::logger()->log(LOG_INFO, "CLient sent a GET request");
            if (request.getRequestLine().getRequestTarget().getPath(config) != "")
                // getPath will have returned an empty string if path is not valid
                Logger::logger()->log(LOG_INFO, "Static file request");
            else
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

// Check if method is allowed by the config file
bool    RequestInterpreter::isAllowedMethod(Config& config)
{
    (void)config;
    // implementation here
    return (true);
}

