#include "webserv.hpp"

HTTPResponse::HTTPResponse() {}

HTTPResponse::~HTTPResponse()
{
    std::cout << "HTTPResponse destructor called" << std::endl;
}

void HTTPResponse::generateResponse(HTTPRequest *request)
{
	getBodyFromFile(request->getUri());
	getHeader(request);
}

std::string HTTPResponse::getResponse()
{
    // Use HTMLParser to modify the HTML content
    htmlParser.parse(fileBody); // Parse the HTML content
    std::string cssUri = htmlParser.extractCSSUri();
    // Include modified HTML in the response
    fullResponse.append(fileHeader);
    fullResponse.append(htmlParser.getModifiedHTML()); // Use modified HTML
    return fullResponse;
}

void    HTTPResponse::getHeader(HTTPRequest *request)
{
	Header header;

	fileHeader = header.createHeader(request);
	std::cout << "fileHeader: " << fileHeader << std::endl;
}

// Takes the uri of the file and copies its' contents to HTTPResponse->fileBody
void     HTTPResponse::getBodyFromFile(std::string uri)
{
    std::string     line;
    std::string     path = "assets";
    path.append(uri, 0, uri.length()); // problem with the uri

    std::ifstream        fs(path.c_str());

    if (fs.is_open())
        std::cout << "File opened: " << path << std::endl;
    while (std::getline(fs, line))
    {
        fileBody.append(line, 0, line.length());
    }
    std::cout << "parsed file: " << fileBody << std::endl;
    fs.close();
}
