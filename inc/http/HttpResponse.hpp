#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <string>
# include "Header.hpp"

class HttpResponse
{
    public:
    // --- Constructors and Destructor ---
        HttpResponse();
        ~HttpResponse();

    // --- Public Methods ---
        // ··· Getters and utils ···  
        std::string         getResponse(std::string uri);
        std::string         getResponseError(int errorCode);

    private:
    // --- Private Methods ---
        void                getBodyFromFile(std::string uri, std::string path);
        void                generateHeaderFromBody();
        std::string         extractStatusText(const std::string& fileName);
        std::string         generateStatusLine(const std::string& fileName, int errorCode); 

        std::string         getCurrentDate();
        std::string         generateErrorHeaders();
    // --- Private Attributes ---

        std::string     headerTemp_;
        std::string     statusLine_;
        Header          header_;
        std::string     body_;
        std::string     fullResponse_;
};

#endif

/*
https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/