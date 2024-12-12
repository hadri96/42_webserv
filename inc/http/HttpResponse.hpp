#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <string>
# include "Header.hpp"
# include "ErrorPage.hpp"

class HttpResponse
{
    public:
    // --- Constructors and Destructor ---
        HttpResponse();
        ~HttpResponse();

    // --- Public Methods ---
        // ··· Getters and utils ···  
        std::string         generateStaticResponse(File& file);
        std::string         generateStaticResponse(ErrorPage& errorPage);
        // std::string         generateStaticResponse(std:::string html);
        // std::string         generateStaticResponse(File& html);
        // std::string         generateStaticResponse(int statusCode, File& errorPage);
    
    private:
    // --- Private Methods ---
        void                        generateBasicHeaders();
        std::string                 getCurrentTime() const;
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