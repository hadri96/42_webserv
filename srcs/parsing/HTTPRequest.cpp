#include "../../includes/webserv.hpp"

HTTPRequest::HTTPRequest() : method("GET"), uri("example_response.html"), body("HEllo server\n\n\n") {}

HTTPRequest::~HTTPRequest() {}

