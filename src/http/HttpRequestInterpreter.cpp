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

    /*
    if (!config.isMethodAllowed(method, request.getUri()))
        return (HttpResponse(createResourceError(config, 405)));

    if (!config.isSizeAllowed(request.getBodySize(), request.getUri()))
        return (HttpResponse(createResourceError(config, 413)));
    */

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
    return (HttpResponse(createResourceFile(config, request)));
    //return (HttpResponse(createResourceError(config, 404)));
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
	const ConfigErrorPage* customErrorPage = config.getConfigErrorPage(code);

	// Do we have a custom error page defined in config and if yes retrieve its path
	if (!customErrorPage)
		return (ResourceDefault(code));
    
	Uri customErrorPageUri = customErrorPage->getUri();
	const Path* customErrorPagePath = config.getPath(customErrorPageUri);

	// If no custom error page path has been found return the default one
	if (!customErrorPagePath)
		return (ResourceDefault(code));

	// Replace x.html by the last digit of the code .
    std::string customErrorPageUriStr = customErrorPageUri;
    std::string toReplace = "x.html";
    std::string replacement = toString(code % 10) + ".html";
    size_t pos = customErrorPageUriStr.find(toReplace);
    if (pos != std::string::npos) {
        customErrorPageUriStr.replace(pos, toReplace.length(), replacement);
    }

    Path customErrorPagePathObj = *customErrorPagePath;
    customErrorPagePathObj = customErrorPagePathObj/customErrorPageUriStr;

	// If the custom error page is not in the file system, return the default one
	if (!(customErrorPagePathObj.getAbsPath().isInFileSystem()))
		return (ResourceDefault(code));

	return (Resource(code, customErrorPagePathObj.getAbsPath().read()));
}

Resource	HttpRequestInterpreter::createResourceFile(Config& config, HttpRequest& request)
{
	Uri     uri = request.getRelativeUri();

    const Path* foundPath = config.getPath(uri);

    if (!foundPath)
        return (createResourceError(config, 404));

    Path path = *foundPath;
    path = path/uri;

    if (!(path.getAbsPath().isInFileSystem()))
        return (createResourceError(config, 404));

    return (Resource(200, path.getAbsPath().read()));


	// check if uri exists 
	// check if directory or file 
        // if directory get index file
    // check if directory listing is on
    // build File object
    // check permissions
	// check if redirection
	// if redirection  return  resourceRedirection

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

    return (createResourceError(config, 404));
}