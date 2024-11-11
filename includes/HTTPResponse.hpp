#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

class HTTPResponse
{
    public:
    // --- Constructors and Destructor ---
        HTTPResponse();
        ~HTTPResponse();

    // --- Public Methods ---
        // ··· Getters and utils ···  
        std::string         getResponse(std::string uri);
        void                getBodyFromFile(std::string uri);
        void                getHeaderFromBody();

    private:
    // --- Private Attributes ---

        std::string     fileHeader;
        std::string     fileBody;
        std::string     fullResponse;
};

#endif