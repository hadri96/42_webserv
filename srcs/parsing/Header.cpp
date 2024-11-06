#include "webserv.hpp"

// Constructor
Header::Header() : status_code(200), contentType("text/plain"), cacheControl("no-cache") {}

// Destructor
Header::~Header() {}

// Check if a file exists
bool Header::fileExists(std::string filepath)
{
    std::ifstream file(filepath);
    return file.good(); // Returns true if the file exists and can be opened
}

// Create the status code based on the method and file path
void Header::createStatusCode()
{
	std::string file = "assets" + request->getUri();
	if (request->getMethod() == "GET")
	{
		if (fileExists(file))
			status_code = 200; // OK
        else
            status_code = 404; // Not Found
    }
    else
        status_code = 405; // Method Not Allowed
}

// Create the content type based on the file extension
void Header::createContentType()
{
	std::string extension = request->getUri().substr(request->getUri().find_last_of('.') + 1);
	if (extension == "html")
        contentType = "text/html; charset=UTF-8";
    else if (extension == "css")
        contentType = "text/css; charset=UTF-8";
    else if (extension == "json")
        contentType = "application/json; charset=UTF-8";
    else
        contentType = "application/octet-stream"; // Default for unknown types
}

// Create custom headers
void Header::createCustomHeaders()
{
	//customHeaders["Content-Length"] = std::to_string(request->getBody().size());
	customHeaders["Date"] = getCurrentTime();
	customHeaders["Connection"] = "close";
}

// Create cache control header
void Header::createCacheControl()
{
    cacheControl = "no-cache"; // Example: Disable caching
}

// Construct the complete header as a string
std::string Header::createHeader(HTTPRequest *request)
{
	this->request = request;
	createStatusCode();
	createContentType();
	createCacheControl();
	createCustomHeaders();

	std::ostringstream headerStream;
    headerStream << request->getHttpVersion() << " " << status_code << " " << responseMessage << "\r\n";
    headerStream << "Content-Type:" << contentType << "\r\n";
    headerStream << "Cache-Control: " << cacheControl << "\r\n";

    // Add custom headers if any
    for (std::map<std::string, std::string>::const_iterator it = customHeaders.begin(); it != customHeaders.end(); ++it)
        headerStream << it->first << ":" << it->second << "\r\n";
    headerStream << "\r\n"; // End of headers
    return headerStream.str();
}
