#include "HttpRequestInterpreter.hpp"
#include "ToString.hpp"
#include "HttpMethodType.hpp"
#include "Logger.hpp"
#include "ResourceDefault.hpp"

#include <string>
#include <stdexcept>
#include <sys/stat.h> // For struct stat and stat()
#include <unistd.h>   // For realpath()
#include <limits.h>   // For PATH_MAX

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequestInterpreter::HttpRequestInterpreter(Server* server)
    : server_(server)
{}

HttpRequestInterpreter::~HttpRequestInterpreter()
{}

// =============================================================================
// Getters
// =============================================================================


// =============================================================================
// Public Methods 
// =============================================================================

HttpResponse   HttpRequestInterpreter::interpret(HttpRequest& request, Config& config)
{
    HttpMethodType      method = request.getMethod();
    HttpResponse        response;


    if (!config.isMethodAllowed(method, request.getUri()))
        return (HttpResponse(createResourceError(config, 405)));

    if (!config.isSizeAllowed(request.getBodySize(), request.getUri()))
        return (HttpResponse(createResourceError(config, 413)));

    if (isCgiRequest(config, request))
        return (HttpResponse(createResourceCgi(config, request)));

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
            throw (HttpRequestInterpreter::BadRequest());
    }
    return (response);
}

// =============================================================================
// Private Methods 
// =============================================================================

// ·············································································
// Method Handlers
// ·············································································

HttpResponse    HttpRequestInterpreter::handleGetRequest(Config& config, HttpRequest& request)
{
    (void) request;
    Logger::logger()->log(LOG_DEBUG, "handleGetRequest...");
    return (HttpResponse(createResourceError(config, 404)));
}


HttpResponse    HttpRequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri     uri = request.getRelativeUri();

    // formulaire POST prenom, nom  --> page php --> salut Mickey Mouse
    // upload de fichier

    Logger::logger()->log(LOG_INFO, config.getServerName());
    // check if resource exists
    // check if resource is allowed
    // get request content length header (check not too big --> 403)
    return (response);
}

HttpResponse    HttpRequestInterpreter::handleDeleteRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri             uri = request.getRelativeUri();

    // allowed to deleter or not --> ResourceError(403)
    // is dir ? 
    // deleteResource(Uri)

    Logger::logger()->log(LOG_INFO, config.getServerName());
    return (response);
}

// ·············································································
// Resource Makers
// ·············································································

# include <iostream>

Resource	HttpRequestInterpreter::createResourceError(Config& config, int code)
{
    Logger::logger()->log(LOG_DEBUG, "handleResourceError...");
	const ConfigErrorPage*  customErrorPage = config.getConfigErrorPage(code);

	if (!customErrorPage)
	{
		 Logger::logger()->log(LOG_DEBUG, "No custom error page found, creating a default one...");
		return (ResourceDefault(code));
	}

	Logger::logger()->log(LOG_DEBUG, "Custom error page URI : " + customErrorPage->getUri());

	const Path* customErrorPagePath = config.getPath(customErrorPage->getUri());

	if (!customErrorPagePath)
	{
		Logger::logger()->log(LOG_DEBUG, "No custom error root path found");
		return (ResourceDefault(code));
	}

	Logger::logger()->log(LOG_DEBUG, std::string("Custom error page root path : ") + customErrorPagePath);
	
	return (ResourceDefault(code));
}

Resource	HttpRequestInterpreter::createResourceFile(Config& config, HttpRequest& request)
{
	Uri     uri = request.getRelativeUri();
	 (void) config;
	// check if uri exists 
	// check if directory or file 
        // if directory get index file
    // check if directory listing is on
    // build File object
    // check permissions
	// check if redirection
	// if redirection  return  resourceRedirection

	return (Resource(200, "File..."));
}

Resource	HttpRequestInterpreter::createResourceDirectoryList(Config& config, Path path)
{
	(void) path;
    (void) config;
	return (Resource(200, "Directory list..."));
}

Resource        HttpRequestInterpreter::createResourceCgi(Config& config, HttpRequest& request)
{
    (void) request;

    if (config.isTypeAllowed(request.getMimeType(), request.getUri()))
        return (createResourceError(config, 415));

    if (request.getMethod() == POST && request.getBody().empty())
        return (createResourceError(config, 400));

    // Check "inputs" field (map) -> correct types
        // 422 Unprocessable Entity
    
    // Check permissions 
        // 401 Unauthorised or 403 Forbidden
    
    // Check duplicate ? Does the resource already exist? 
        // 409 Conflict

    // check amount of requests? 
        // 429 too many requests
    
    // protect from sql injection
    
    // Prepare CGI environment
    // char**   envp = prepareCgiEnvironment(config, request);

    // Run CGI script in new process (fork())

    // create response with CGI script output

    return (createResourceError(config, 404));
}

// ·············································································
// Utils
// ·············································································

bool    HttpRequestInterpreter::isCgiRequest(Config& config, HttpRequest& request)
{
    Path                        realPath = *(config.getPath(request.getUri()));
    std::vector<std::string>    pathComponents = realPath.getComponents();

    for (size_t i = 0; i < pathComponents.size(); i++)
    {
        if (pathComponents[i].find("/cgi-bin/") != std::string::npos || 
                pathComponents[i].find(config.getCgiDir()) != std::string::npos ||
                pathComponents[i].find(".php") != std::string::npos || 
                pathComponents[i].find(".py") != std::string::npos || 
                pathComponents[i].find(".cgi") != std::string::npos)
        {
            return (true);
        }
    }
    return (false); 
}
/*
char**   HttpRequestInterpreter::prepareCgiEnvironment(Config& config, HttpRequest& request)
{
    std::map<std::string, std::string> env;

    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["REQUEST_METHOD"] = HttpMethodTypeToString(request.getMethod());
    env["SCRIPT_FILENAME"] = config.getPath(request.getUri());
    env["PATH_INFO"] = config.getPath(request.getUri());
    
    return ((char **)env);
}    
*/