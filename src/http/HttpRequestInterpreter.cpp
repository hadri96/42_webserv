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
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <iostream>
#include <cstdio>


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
	{
    	HttpResponse 	errorResponse(createResourceError(config, 405));
    	return (errorResponse);
	}


	if (!config.isSizeAllowed(request.getBodySize(), request.getUri()))
	{
		HttpResponse	errorResponse = HttpResponse(createResourceError(config, 413));
		return (errorResponse);
	}

	switch (method)
	{
		case GET:
			Logger::logger()->log(LOG_INFO, "Client sent a GET request");
			response = handleGetRequest(config, request);
			break;
		case POST:
			Logger::logger()->log(LOG_INFO, "Client sent a POST request");
			response = handlePostRequest(config, request);
			break;
		case DELETE:
			Logger::logger()->log(LOG_INFO, "Client sent a DELETE request");
			response = handleDeleteRequest(config, request);
			break;
		case UNKNOWN:
			Logger::logger()->log(LOG_WARNING, "Received UNKNOWN request method");
			HttpResponse 	errorResponse(createResourceError(config, 400));
			return (errorResponse);
			break;
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
}

HttpResponse    HttpRequestInterpreter::handlePostRequest(Config& config, HttpRequest& request)
{
	Uri                 uri = request.getUri();
	Resource* 			resource = createResourceFile(config, request);

	return (HttpResponse(resource));
}

HttpResponse HttpRequestInterpreter::handleDeleteRequest(Config& config, HttpRequest& request)
{
    Uri 			uri = request.getUri();
    Path 			filePath = *config.getPath(uri);
	filePath = filePath / uri;
	Path			absFilePath = filePath.getAbsPath();
	std::string		pathString = absFilePath;

	Logger::logger()->log(LOG_DEBUG, "pathString : " + pathString);

    if (access(pathString.c_str(), W_OK) != 0) 
	{
        Logger::logger()->log(LOG_WARNING, "DELETE request: Permission denied");
        return HttpResponse(createResourceError(config, 403));
    }
	Logger::logger()->log(LOG_ERROR, "HELLOOO");
    if (remove(pathString.c_str()) != 0) 
	{
        Logger::logger()->log(LOG_ERROR, "DELETE request: Failed to delete resource");
        return HttpResponse(createResourceError(config, 500)); 
    }

    Logger::logger()->log(LOG_INFO, "DELETE request: Resource deleted successfully");
	Resource* 		resource = new Resource(204, "File deleted successfully");
	return HttpResponse(resource);
}

// ·············································································
// Resource Makers
// ·············································································

# include <iostream>

Resource*	HttpRequestInterpreter::createResourceError(Config& config, int code)
{
	const   ConfigErrorPage*    customErrorPage = config.getConfigErrorPage(code);
	if (!customErrorPage)
		return (new ResourceDefault(code));
	Uri                         customErrorPageUri = customErrorPage->getUri();
	const Path*                 customErrorPagePath = config.getPath(customErrorPageUri);
	if (!customErrorPagePath)
		return (new ResourceDefault(code));

	// Replace x.html by the last digit of the code .
	std::string                 customErrorPageUriStr = customErrorPageUri;
	std::string                 toReplace = "x.html";
	std::string                 replacement = toString(code % 10) + ".html";
	size_t                      pos = customErrorPageUriStr.find(toReplace);

	if (pos != std::string::npos) 
		customErrorPageUriStr.replace(pos, toReplace.length(), replacement);

	Path                        customErrorPagePathObj = *customErrorPagePath;

	customErrorPagePathObj = static_cast<Path>(customErrorPagePathObj) / customErrorPageUriStr;

	if (!(customErrorPagePathObj.getAbsPath().isInFileSystem()))
		return (new ResourceDefault(code));

	return (new Resource(code, customErrorPagePathObj.getAbsPath().read()));
}

Resource*	HttpRequestInterpreter::createResourceRedirection(Config& config, HttpRequest& request)
{
	Uri     				uri = request.getUri();
	const ConfigLocation* 	configLocation = config.getConfigLocation(uri);
	int 					statusCode = configLocation->getConfigRedirection().getStatusCode();
	Uri 					redirUri = configLocation->getConfigRedirection().getUri();

	return (new ResourceRedirection(statusCode, redirUri));
}

Resource*	HttpRequestInterpreter::createResourceFile(Config& config, HttpRequest& request)
{
	Uri                 uri = request.getUri();
	const Path*         rootPath = config.getPath(uri);
	if (!rootPath)
	{
		Logger::logger()->log(LOG_DEBUG, "createResourceFile : no root path in config matching the uri");
		return (createResourceError(config, 404));
	}

	// Check if there is a redirection in location block
	// Get the location that matches the URI
	const ConfigLocation* 		configLocation = config.getConfigLocation(uri);
	const ConfigRedirection 	configRedirection = configLocation->getConfigRedirection();

	if (configRedirection.getStatusCode() != 0)
	{
		Logger::logger()->log(LOG_DEBUG, "createResourceFile : redirection set in location block");
		return (createResourceRedirection(config, request));
	}

	/*
	// Check if there is a redirection in server block
	if (config.getConfigRedirection().getStatusCode() != 0)
	{
		Logger::logger()->log(LOG_DEBUG, "createResourceFile : redirection set in server block");
		return (new ResourceRedirection(config.getConfigRedirection().getStatusCode(), config.getConfigRedirection().getUri()));
		//return (createResourceRedirection(config, request));
	}
	*/

	// Appends the URI to the root path
	Path            path = *rootPath;
	path = static_cast<Path>(path) / uri;

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
	
	if (path.getExtension() == "php")
	{
		Logger::logger()->log(LOG_DEBUG, "createResourceFile : the resource is a php script");
		return (createResourceCgi(config, request));
	}

	Resource*       resource = new Resource(200, path.getAbsPath().read());
	HttpMimeTypes   httpMimeTypes;
	std::string     extension = path.getExtension();
	std::string     mimeType = httpMimeTypes.getMimeType(extension);

	// Logger::logger()->log(LOG_DEBUG, "createResourceFile : resource file extension : " + extension);
	// Logger::logger()->log(LOG_DEBUG, "createResourceFile : resource file mime type : " + mimeType);

	resource->setMimeType(mimeType);
	return (resource);
}

Resource*	HttpRequestInterpreter::createResourceDirectory(Config& config, HttpRequest& request)
{
	Uri                         uri = request.getUri(); // (REVISIT : was already done earlier)
	const Path*                 rootPath = config.getPath(uri); //(REVISIT : was already done earlier)
	Path                        path = *rootPath; //(REVISIT : was already done earlier)
	
	path = static_cast<Path>(path) / uri;

	const ConfigLocation*       configLocation = config.getConfigLocation(uri);

	// Display the default page if autoindex is off
	if (!configLocation->getAutoIndex())
	{
		Logger::logger()->log(LOG_DEBUG, "createResourceDirectory : autoindex is off");
		// REVISIT : Implement custom default file
		//if (configLocation->getDefaultFile())

		Path customIndex = configLocation->getDefaultFile();
		Path indexPath = path/customIndex;

		if (std::string(customIndex) == "/")
			indexPath = path/"index.html";
		
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

	DIR                         *dir;
	struct dirent               *entry;
	std::string                 pathStr = path.getAbsPath();
	const char                  *absPath = pathStr.c_str();

	// Open the directory
	dir = opendir(absPath);
	if (dir == NULL) {
		Logger::logger()->log(LOG_DEBUG, "createResourceDirectory: Failed to open directory : " + pathStr);
		return createResourceError(config, 404);
	}

	std::string                 directoryListing = "<h1>Index of " + uri + "</h1><table><tr><td><a href=\"" + uri.getParent() + "\">../</a></td></tr>";

	// Read and accumulate directory contents
	while ((entry = readdir(dir)) != NULL) 
	{
		std::string             entryName(entry->d_name);
	
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
	Cgi             cgi(config, request);
	std::string     cgiOutput;

	if (cgi.runCgi(cgiOutput, request) != 0)
		return (createResourceError(config, 500));

	Resource*       cgiResource = new Resource(200, cgiOutput);
	cgiResource->setMimeType("text/html");

	return (cgiResource);
}

// ·············································································
// Utils
// ·············································································


bool    HttpRequestInterpreter::isValidToken(std::string token)
{
	if (!token.empty())
		return (true);
	return (false);
}