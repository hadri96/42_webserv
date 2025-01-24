#ifndef HTTP_METHOD_TYPE_HPP
# define HTTP_METHOD_TYPE_HPP

#include <string>

enum	HttpMethodType
{
	GET,
	POST,
	DELETE,
	UNDEFINED
};

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

#endif
