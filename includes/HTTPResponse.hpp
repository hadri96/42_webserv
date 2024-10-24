#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

class HTTPResponse
{
    public:
    // Constructors & destructors 
    HTTPResponse();
    ~HTTPResponse();

    // Methods
    std::string         getResponse(std::string uri);
    void                getBodyFromFile(std::string uri);
    void                getHeaderFromBody();

    private:
    std::string     fileHeader;
    std::string     fileBody;
    std::string     fullResponse;
};

#endif