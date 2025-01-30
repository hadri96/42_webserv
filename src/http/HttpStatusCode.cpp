#include "HttpStatusCode.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpStatusCode::HttpStatusCode(void)
{
    // 1xx: Informational
    addStatusCode(100, "Continue", "The server has received the request headers and the client should proceed to send the request body.");
    addStatusCode(101, "Switching Protocols", "The server is switching protocols as requested by the client.");
    addStatusCode(102, "Processing", "The server is processing the request but no response is available yet.");
    addStatusCode(103, "Early Hints", "Used to return some response headers before the final HTTP message.");

    // 2xx: Success
    addStatusCode(200, "OK", "The request has succeeded.");
    addStatusCode(201, "Created", "The request has been fulfilled and a new resource has been created.");
    addStatusCode(202, "Accepted", "The request has been accepted for processing, but the processing has not been completed.");
    addStatusCode(203, "Non-Authoritative Information", "The server is a transforming proxy that received a 200 OK from its origin, but is returning a modified version of the origin's response.");
    addStatusCode(204, "No Content", "The server successfully processed the request but is not returning any content.");
    addStatusCode(205, "Reset Content", "The server successfully processed the request, but is not returning any content, and requires that the requester reset the document view.");
    addStatusCode(206, "Partial Content", "The server is delivering only part of the resource due to a range header sent by the client.");
    addStatusCode(207, "Multi-Status", "The message body that follows is an XML message and can contain a number of separate response codes, depending on how many sub-requests were made.");
    addStatusCode(208, "Already Reported", "The members of a DAV binding have already been enumerated in a previous reply to this request, and are not being included again.");
    addStatusCode(226, "IM Used", "The server has fulfilled a GET request for the resource, and the response is a representation of the result of one or more instance-manipulations applied to the current instance.");

    // 3xx: Redirection
    addStatusCode(300, "Multiple Choices", "The request has more than one possible response. The user agent or user should choose one of them.");
    addStatusCode(301, "Moved Permanently", "The requested resource has been permanently moved to a new location.");
    addStatusCode(302, "Found", "The requested resource is temporarily located at a different URL.");
    addStatusCode(303, "See Other", "The response to the request can be found under a different URI and should be retrieved using a GET method.");
    addStatusCode(304, "Not Modified", "Indicates that the resource has not been modified since the version specified by the request headers.");
    addStatusCode(305, "Use Proxy", "The requested resource must be accessed through the proxy given by the Location field.");
    addStatusCode(307, "Temporary Redirect", "The request should be repeated with another URI, but future requests should still use the original URI.");
    addStatusCode(308, "Permanent Redirect", "The request and all future requests should be repeated using another URI.");

    // 4xx: Client Errors
    addStatusCode(400, "Bad Request", "The server cannot process the request due to a client error.");
    addStatusCode(401, "Unauthorized", "The request requires user authentication.");
    addStatusCode(402, "Payment Required", "Reserved for future use.");
    addStatusCode(403, "Forbidden", "You do not have permission to access this resource.");
    addStatusCode(404, "Not Found", "The page or resource you requested could not be found on this server.");
    addStatusCode(405, "Method Not Allowed", "The method specified in the request is not allowed for the resource.");
    addStatusCode(406, "Not Acceptable", "The server cannot produce a response matching the list of acceptable values defined in the request's headers.");
    addStatusCode(407, "Proxy Authentication Required", "The client must first authenticate itself with the proxy.");
    addStatusCode(408, "Request Timeout", "The server timed out waiting for the request.");
    addStatusCode(409, "Conflict", "The request could not be completed due to a conflict with the current state of the resource.");
    addStatusCode(410, "Gone", "The requested resource is no longer available and will not be available again.");
    addStatusCode(411, "Length Required", "The request did not specify the length of its content, which is required by the requested resource.");
    addStatusCode(412, "Precondition Failed", "The server does not meet one of the preconditions specified in the request.");
    addStatusCode(413, "Payload Too Large", "The request entity is larger than limits defined by the server.");
    addStatusCode(414, "URI Too Long", "The URI provided was too long for the server to process.");
    addStatusCode(415, "Unsupported Media Type", "The request entity has a media type which the server or resource does not support.");
    addStatusCode(416, "Range Not Satisfiable", "The client has asked for a portion of the file, but the server cannot supply that portion.");
    addStatusCode(417, "Expectation Failed", "The server cannot meet the requirements of the Expect request-header field.");
    addStatusCode(418, "I'm a teapot", "The server refuses the attempt to brew coffee with a teapot.");
    addStatusCode(421, "Misdirected Request", "The request was directed at a server that is not able to produce a response.");
    addStatusCode(422, "Unprocessable Entity", "The request was well-formed but was unable to be followed due to semantic errors.");
    addStatusCode(423, "Locked", "The resource that is being accessed is locked.");
    addStatusCode(424, "Failed Dependency", "The request failed because it depended on another request and that request failed.");
    addStatusCode(425, "Too Early", "The server is unwilling to risk processing a request that might be replayed.");
    addStatusCode(426, "Upgrade Required", "The client should switch to a different protocol.");
    addStatusCode(428, "Precondition Required", "The origin server requires the request to be conditional.");
    addStatusCode(429, "Too Many Requests", "The user has sent too many requests in a given amount of time.");
    addStatusCode(431, "Request Header Fields Too Large", "The server is unwilling to process the request because its header fields are too large.");
    addStatusCode(451, "Unavailable For Legal Reasons", "The server is denying access to the resource as a consequence of a legal demand.");

    // 5xx: Server Errors
    addStatusCode(500, "Internal Server Error", "The server encountered an unexpected condition that prevented it from fulfilling the request.");
    addStatusCode(501, "Not Implemented", "The server does not support the functionality required to fulfill the request.");
    addStatusCode(502, "Bad Gateway", "The server received an invalid response from an inbound server it accessed while attempting to fulfill the request.");
    addStatusCode(503, "Service Unavailable", "The server is currently unable to handle the request due to temporary overloading or maintenance of the server.");
    addStatusCode(504, "Gateway Timeout", "The server did not receive a timely response from an upstream server.");
    addStatusCode(505, "HTTP Version Not Supported", "The server does not support the HTTP protocol version used in the request.");
    addStatusCode(506, "Variant Also Negotiates", "Transparent content negotiation for the request results in a circular reference.");
    addStatusCode(507, "Insufficient Storage", "The server is unable to store the representation needed to complete the request.");
    addStatusCode(508, "Loop Detected", "The server detected an infinite loop while processing the request.");
    addStatusCode(510, "Not Extended", "Further extensions to the request are required for the server to fulfill it.");
    addStatusCode(511, "Network Authentication Required", "The client needs to authenticate to gain network access.");
}

HttpStatusCode::HttpStatusCode(const HttpStatusCode& other)
{
    (void) other;
}

HttpStatusCode::~HttpStatusCode(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpStatusCode&   HttpStatusCode::operator=(const HttpStatusCode& rhs)
{
    (void) rhs;
    return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

std::string  HttpStatusCode::getStatusLine(int code)
{
    for (size_t i = 0; i != code_.size(); ++i)
    {
        if (code_[i] == code)
            return (statusLine_[i]);
    }

    return ("");
}

std::string  HttpStatusCode::getMessage(int code)
{
    for (size_t i = 0; i != code_.size(); ++i)
    {
        if (code_[i] == code)
            return (message_[i]);
    }
    return ("");
}


// =============================================================================
// Private Methods
// =============================================================================

void    HttpStatusCode::addStatusCode(int code, std::string statusLine, std::string message)
{
    code_.push_back(code);
    statusLine_.push_back(statusLine);
    message_.push_back(message);
}