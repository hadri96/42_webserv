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