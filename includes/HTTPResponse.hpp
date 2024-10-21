#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

class HTTPResponse
{
    public:
    // Constructors & destructors 
    HTTPResponse();
    ~HTTPResponse();

    // Methods
    std::string     getParsedResponse();

    private:
    std::string     status;
    std::string     header;
    std::string     body;
    std::string     parsed_response;
};

#endif