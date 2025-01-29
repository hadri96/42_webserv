#include "HttpRequestInterpreter.hpp"
#include "ToString.hpp"
#include "HttpMethodType.hpp"
#include "Logger.hpp"


#include "ResourceDefault.hpp"
#include "ResourceRedirection.hpp"

#include "Cgi.hpp"
#include "HttpMimeTypes.hpp"

#include <string>
#include <stdexcept>
#include <sys/stat.h> // For struct stat and stat()
#include <unistd.h>   // For realpath()
#include <limits.h>   // For PATH_MAX
#include <dirent.h>   // opendir, readdir, closedir

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

    // if (!config.isMethodAllowed(method, request.getUri()))
    //     return (HttpResponse(createResourceError(config, 405)));

    // if (!config.isSizeAllowed(request.getBodySize(), request.getUri()))
    //     return (HttpResponse(createResourceError(config, 413)));

    // REVISIT : Disabled because of some path error
    
    if (isCgiRequest(config, request))
    {   
        Logger::logger()->log(LOG_DEBUG, "Is a CGI Request"); 
        return (HttpResponse(createResourceCgi(config, request)));
    } 

    switch (method)
    {
        case GET:
            Logger::logger()->log(LOG_INFO, "Client sent a GET request");
            response = handleGetRequest(config, request);
            break;
        case POST:
            Logger::logger()->log(LOG_INFO, "Client sent a POST request");
            // get request content length header (if too big --> 403)
            response = handlePostRequest(config, request);
            break;
        case DELETE:
            Logger::logger()->log(LOG_INFO, "Client sent a DELETE request");
            response = handleDeleteRequest(config, request);
            break;
        case UNKNOWN:
            break;
            //throw (HttpRequestInterpreter::BadRequest());
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
    Resource* resource = createResourceFile(config, request);
    Logger::logger()->log(LOG_DEBUG, "handleGetRequest...");

    return (HttpResponse(resource));
    //return (HttpResponse(createResourceError(config, 404)));
}


HttpResponse    HttpRequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
{
    HttpResponse	response;
    Uri     uri = request.getUri();

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
    Uri             uri = request.getUri();

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

Resource*	HttpRequestInterpreter::createResourceError(Config& config, int code)
{
    Logger::logger()->log(LOG_DEBUG, "handleResourceError...");
	const ConfigErrorPage*  customErrorPage = config.getConfigErrorPage(code);

	// Do we have a custom error page defined in config and if yes retrieve its path
	if (!customErrorPage)
		return (new ResourceDefault(code));
    
	Uri customErrorPageUri = customErrorPage->getUri();
	const Path* customErrorPagePath = config.getPath(customErrorPageUri);

	// If no custom error page path has been found return the default one
	if (!customErrorPagePath)
		return (new ResourceDefault(code));

	// Replace x.html by the last digit of the code .
    std::string customErrorPageUriStr = customErrorPageUri;
    std::string toReplace = "x.html";
    std::string replacement = toString(code % 10) + ".html";
    size_t pos = customErrorPageUriStr.find(toReplace);
    if (pos != std::string::npos) {
        customErrorPageUriStr.replace(pos, toReplace.length(), replacement);
    }

    Path customErrorPagePathObj = *customErrorPagePath;
    customErrorPagePathObj = static_cast<Path>(customErrorPagePathObj) / customErrorPageUriStr;
    // customErrorPagePathObj = customErrorPagePathObj/customErrorPageUriStr;

	// If the custom error page is not in the file system, return the default one
	if (!(customErrorPagePathObj.getAbsPath().isInFileSystem()))
		return (new ResourceDefault(code));

	return (new Resource(code, customErrorPagePathObj.getAbsPath().read()));
}

Resource*	HttpRequestInterpreter::createResourceRedirection(Config& config, HttpRequest& request)
{
	// Extract the URI from the request
	Uri     uri = request.getUri();

	// Get the location that matches the URI
    const ConfigLocation* configLocation = config.getConfigLocation(uri);

	int statusCode = configLocation->getConfigRedirection().getStatusCode();
	Uri redirUri = configLocation->getConfigRedirection().getUri();

	return (new ResourceRedirection(statusCode, redirUri));
}

Resource*	HttpRequestInterpreter::createResourceFile(Config& config, HttpRequest& request)
{
    // Extract the URI from the request
	Uri     uri = request.getUri();

    // Get the root path corresponding to the URI
    const Path* rootPath = config.getPath(uri);

    // Error 404 if there is no root path in config matching the uri
    if (!rootPath)
    {
        Logger::logger()->log(LOG_DEBUG, "createResourceFile : no root path in config matching the uri");
        return (createResourceError(config, 404));
    }

	// Check if there is a redirection in location block
	// Get the location that matches the URI
    const ConfigLocation* configLocation = config.getConfigLocation(uri);
	const ConfigRedirection configRedirection = configLocation->getConfigRedirection();

	if (configRedirection.getStatusCode() != 0)
	{
		Logger::logger()->log(LOG_DEBUG, "createResourceFile : redirection set in location block");
		return (createResourceRedirection(config, request));
	}


    // Appends the URI to the root path
    Path path = *rootPath;
    path = static_cast<Path>(path) / uri;
    // path = path/uri;

    Logger::logger()->log(LOG_DEBUG, "createResourceFile : path : " + path.getAbsPath());

    // If the resource is a directory, pass the task to the appropriate handler
    if (path.getAbsPath().isDir())
    {
        Logger::logger()->log(LOG_DEBUG, "createResourceFile : the resource is a directory");
        return (createResourceDirectory(config, request));

    }

    // Error 404 if the resource does not exist
    if (!(path.getAbsPath().isInFileSystem()))
    {
        Logger::logger()->log(LOG_DEBUG, "createResourceFile : the resource does not exist (error 404)");
        return (createResourceError(config, 404));
    }

   
    Resource* resource = new Resource(200, path.getAbsPath().read());

    HttpMimeTypes httpMimeTypes;
    std::string extension = path.getExtension();
    std::string mimeType = httpMimeTypes.getMimeType(extension);

    Logger::logger()->log(LOG_DEBUG, "createResourceFile : resource file extension : " + extension);
    Logger::logger()->log(LOG_DEBUG, "createResourceFile : resource file mime type : " + mimeType);

    resource->setMimeType(mimeType);
    return (resource);
}

Resource*	HttpRequestInterpreter::createResourceDirectory(Config& config, HttpRequest& request)
{
    // Extract the URI from the request (REVISIT : was already done earlier)
	Uri     uri = request.getUri();

    // Get the root path corresponding to the URI (REVISIT : was already done earlier)
    const Path* rootPath = config.getPath(uri);

    // Appends the URI to the root path (REVISIT : was already done earlier)
    Path path = *rootPath;
    path = static_cast<Path>(path) / uri;

    // Get the location that matches the URI
    const ConfigLocation* configLocation = config.getConfigLocation(uri);

    // Display the default page if autoindex is off
    if (!configLocation->getAutoIndex())
    {
        Logger::logger()->log(LOG_DEBUG, "createResourceDirectory : autoindex is off");
        // REVISIT : Implement custom default file
        //if (configLocation->getDefaultFile())

        Path indexPath = path/"index.html";
        Logger::logger()->log(LOG_DEBUG, "createResourceDirectory : index file path " + indexPath.getAbsPath());
        if (!(indexPath.getAbsPath().isInFileSystem()))
        {
            Logger::logger()->log(LOG_DEBUG, "createResourceDirectory : index file not found (error 403) and autoindex off");
            return (createResourceError(config, 403));
        }

        Logger::logger()->log(LOG_DEBUG, "createResourceDirectory : index file found");
        Resource* resource = new Resource(200, indexPath.getAbsPath().read());
        return (resource);
    }
    Logger::logger()->log(LOG_DEBUG, "createResourceDirectory : autoindex is on");

    DIR *dir;
    struct dirent *entry;
    std::string pathStr = path.getAbsPath();
    const char *absPath = pathStr.c_str();

    // Open the directory
    dir = opendir(absPath);
    if (dir == NULL) {
        Logger::logger()->log(LOG_DEBUG, "createResourceDirectory: Failed to open directory : " + pathStr);
        return createResourceError(config, 404);
    }

    std::string directoryListing = "<h1>Index of " + uri + "</h1><table><tr><td><a href=\"" + uri.getParent() + "\">../</a></td></tr>";

    // Read and accumulate directory contents
    while ((entry = readdir(dir)) != NULL) {
        // Use std::string to avoid strcmp
        std::string entryName(entry->d_name);

        
        // Skip . and .. (current and parent directories)
        if (entryName != "." && entryName != "..")
        {
            directoryListing.append("<tr><td><a href=\"" + uri/entryName + "\">");
            directoryListing.append(entryName);
            directoryListing.append("</a></td>");
            directoryListing.append("</tr>\n");
        }
    }

    directoryListing.append("</table>");

    // Close the directory
    closedir(dir);

	return (new Resource(200, directoryListing));
}

Resource*        HttpRequestInterpreter::createResourceCgi(Config& config, HttpRequest& request)
{
    (void) request;

    // if (config.isTypeAllowed(request.getMimeType(), request.getUri()))
    //     return (createResourceError(config, 415));

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

    Cgi     cgi(config, request);

    std::string     cgiOutput;

    if (cgi.runCgi(cgiOutput) != 0)
        return (createResourceError(config, 500));

    // Create a Resource object with CGI output
    Resource* cgiResource = new Resource(200, cgiOutput);
    cgiResource->setMimeType("text/html");

    return (cgiResource);
}

// ·············································································
// Utils
// ·············································································

bool    HttpRequestInterpreter::isCgiRequest(Config& config, HttpRequest& request)
{
    Logger::logger()->log(LOG_DEBUG, "request uri : " + request.getUri());
    const Path*                 pathPtr = config.getPath(request.getUri()); 
    // const Path                  pathCgi = Path("/www/cgi-bin");
    // const Path*                 pathPtr = &pathCgi;
    
    if (pathPtr == NULL)
    {   
        Logger::logger()->log(LOG_DEBUG, "path from config is NULL, it's not a CGI request"); 
        return (false);
    }
    
    Path                        realPath = *pathPtr;
    std::vector<std::string>    pathComponents = realPath.getComponents();

    Logger::logger()->log(LOG_DEBUG, "real path = " + realPath);
    for (size_t i = 0; i < pathComponents.size(); i++)
    {
        Logger::logger()->log(LOG_DEBUG, "path component: " + pathComponents[i]);
        if (pathComponents[i].find("cgi-bin") != std::string::npos || 
                pathComponents[i].find(config.getCgiDir()) != std::string::npos ||
                pathComponents[i].find(".php") != std::string::npos || 
                pathComponents[i].find(".py") != std::string::npos || 
                pathComponents[i].find(".cgi") != std::string::npos)
        {
            Logger::logger()->log(LOG_DEBUG, "It's a CGI request all right");
            return (true);
        }
    }
    Logger::logger()->log(LOG_DEBUG, "It's not a CGI request");
    return (false); 
}

