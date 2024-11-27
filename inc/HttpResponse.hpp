#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <string>

class HttpResponse
{
    public:
    // --- Constructors and Destructor ---
        HttpResponse();
        ~HttpResponse();

    // --- Public Methods ---
        std::string         generateResponse(std::string uri);
        
    // ··· Getters and utils ···  
    
    private:
    // --- Private Attributes ---

        int             statusCode_;
        std::string     responseHeader_;
        std::string     fileBody_;
        std::string     fullResponse_;

    // --- Private Methods ---
    void                getBodyFromFile(std::string uri);
    void                generateHeader();
    std::string         generateStatusLine(int statusCode);

};

#endif



/*
Check the method in the HTTP request (GET, POST, PUT, etc.) and respond accordingly:

a. GET Method
Used to retrieve resources.

200 OK: Resource is successfully found and sent in the response.
404 Not Found: The requested resource does not exist.
403 Forbidden: The server understands the request but refuses to authorize it (e.g., restricted files).
500 Internal Server Error: An unexpected server issue occurred while trying to handle the request.


b. POST Method
Used to submit data (e.g., a form submission).

201 Created: The request was successful, and a new resource was created.
400 Bad Request: The submitted data is invalid or incomplete.
403 Forbidden: The server does not allow this action (e.g., restricted endpoint).
500 Internal Server Error: An error occurred while processing the data.


c. PUT Method
Used to update or create a resource.

200 OK: The resource was successfully updated.
201 Created: The resource was successfully created.
404 Not Found: The resource to be updated does not exist.
500 Internal Server Error: The update or creation failed due to a server issue.


d. DELETE Method
Used to delete a resource.

200 OK: The resource was successfully deleted.
204 No Content: The resource was deleted, and no additional content is provided.
404 Not Found: The resource does not exist.
403 Forbidden: The server refuses to delete the resource.


e. Other Methods
501 Not Implemented: The server does not support the method.


*/