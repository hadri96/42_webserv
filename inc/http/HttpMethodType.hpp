#ifndef HTTP_METHOD_TYPE_HPP
# define HTTP_METHOD_TYPE_HPP

#include <string>

enum	HttpMethodType
{
	GET,
	POST,
	DELETE,
	UNKNOWN
};

// Convert HttpMethodType to string
inline std::string httpMethodToString(HttpMethodType method)
{
    switch (method)
	{
        case GET: return ("GET");
        case POST: return ("POST");
        case DELETE: return ("DELETE");
        default: return ("UNKNOWN");
    }
}

// Convert string to HttpMethodType
inline HttpMethodType stringToHttpMethod(const std::string& methodStr)
{
    if (methodStr == "GET") return (GET);
	if (methodStr == "POST") return (POST);
    if (methodStr == "DELETE") return (DELETE);   
    return (UNKNOWN);
}

/*
// REVISIT : TO REMOVE ? 

inline std::string HttpMethodTypeToString(HttpMethodType method)
{
	switch (method)
	{
		case GET:       
			return "GET";
		case POST:      
			return "POST";
		case DELETE:    
			return "DELETE";
		case UNDEFINED: 
			return "UNDEFINED";
		default:        
			return "UNKNOWN";
	}
}
*/

#endif
