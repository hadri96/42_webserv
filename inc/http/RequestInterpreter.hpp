#ifndef REQUESTINTERPRETER_HPP
# define REQUESTINTERPRETER_HPP

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include "Server.hpp"
# include "Config.hpp"

class RequestInterpreter 
{
    public:
    // --- Constructors and Destructor ---
        RequestInterpreter(Server* server);
        ~RequestInterpreter();

    // --- Public Methods ---
        void        interpret(HttpRequest& request, Config& config);
        
    // ··· Getters and utils ···  


    // ··· Exceptions ···  
        class BadRequest : public std::exception
        {
            public:
                const char  *what() const throw()
                {
                    return ("Bad Request (400)");
                };
        };


    private:
    // --- Private Attributes ---
        Server*     server_;

    // --- Private Methods ---
        void        handleGetRequest(Config& config, HttpRequest& request);
        void        handlePostRequest(Config& config, HttpRequest& request);
        void        handleDeleteRequest(Config& config, HttpRequest& request);

        bool        fileInServer(std::string uri, Config& config);
        bool        isAllowedMethod(Config& config);
};

#endif

/*

GET Method
Purpose: Retrieve a resource.

Information Needed From HttpRequest:

The requested URI (getRelativeUri()).
Headers (e.g., If-Modified-Since for caching behavior).
Query string parameters (if applicable).

Information Needed From Config:

Mapping of the requested URI to an actual file or directory.
Index file for directory URIs (e.g., serve /index.html if / is requested).
File existence and permissions.
Error pages (e.g., for 404 Not Found or 403 Forbidden).
Redirection rules (e.g., if the URI maps to another location).

Potential Responses:
200 OK: Serve the requested file or directory index.
301/302 Redirect: Redirect to another URI based on configuration.
404 Not Found: Resource does not exist.
403 Forbidden: Access to the resource is denied.
304 Not Modified: If If-Modified-Since header matches file metadata.



POST Method
Purpose: Submit data to the server.

Information Needed From HttpRequest:

URI (getRelativeUri()).
Headers (e.g., Content-Type for parsing the body, Content-Length for size validation).
Body content (e.g., form data, JSON, file upload).

Information Needed From Config:

Target endpoint and whether POST is allowed for this URI.
Maximum request body size.
Permissions for write or append operations.
Mapping for specific actions (e.g., a script to handle form submissions).
Error pages for oversize bodies or unsupported media types.

Potential Responses:
200 OK: Successfully processed the request.
201 Created: Successfully created a new resource.
400 Bad Request: Malformed request body or missing data.
403 Forbidden: POST method not allowed for this URI.
413 Payload Too Large: Request body exceeds maximum allowed size.
415 Unsupported Media Type: Content-Type is not supported.
500 Internal Server Error: Server failed to process the request.


DELETE Method
Purpose: Remove a resource.

Information Needed From HttpRequest:

URI (getRelativeUri()).
Headers (e.g., any custom headers for authorization or additional metadata).

Information Needed From Config:

Target file or resource location.
Permissions to delete the specified resource.
Directory traversal restrictions (to prevent deletion of unintended files).
Error pages for failures (e.g., file not found or insufficient permissions).

Potential Responses
200 OK: Successfully deleted the resource.
202 Accepted: Deletion is queued but not yet completed.
204 No Content: Successfully deleted but no content to return.
403 Forbidden: DELETE method not allowed for this URI.
404 Not Found: Resource does not exist.
409 Conflict: Cannot delete a resource because of dependencies (e.g., a non-empty directory).
500 Internal Server Error: Server failed to delete the resource.


*/