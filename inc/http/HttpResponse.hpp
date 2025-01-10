#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <string>
# include "Header.hpp"
# include "Config.hpp"
# include "ErrorPage.hpp"

class HttpResponse
{
    public:
    // --- Constructors and Destructor ---
        HttpResponse();
        HttpResponse(File& file);
        HttpResponse(ErrorPage& errorPage);
        ~HttpResponse();

    // --- Public Methods ---
        // ··· Getters and utils ···  
        HttpResponse&       generateError(Config& config, int errorCode);

        std::string         getFullResponse() const;
        std::string         getHeaders() const;
    
    private:
    // --- Private Methods ---
        void                        generateBasicHeaders();
        // std::string                 getCurrentTime() const;
        void                        composeFullResponse();

        // --- Error Response Methods ---
        std::string                 extractStatusText() const;
        void                        errorStatusLine(ErrorPage& errorPage); 
        
        // --- Static Response Methods ---
        void                        staticStatusLine();


    // --- Private Attributes ---

        std::string     headers_;
        std::string     statusLine_;
        std::string     body_;
        std::string     fullResponse_;

        // Header          header_;
};

#endif

/*
https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/