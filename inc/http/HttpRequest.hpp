#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "RequestLine.hpp"
# include "Header.hpp"

# include <string>

class HttpRequest 
{
    public:
    // --- Constructors and Destructor ---
        HttpRequest();
        ~HttpRequest();

    // --- Public Methods ---
        void            appendRequest(std::string input);
        
        // ··· Getters and utils ···  
        std::string     getRawRequest();


    private:
    // --- Private Attributes ---
        std::string     rawRequest; // full unparsed string of the request
        // Not ideal for very long requests, which should be read in chunks rather than saved into memory
        
        RequestLine     requestLine_; // contains httpMethodType, requestTarget(path), HttpVersion
        Header          header_; // contains all header information
        std::string     body_;

};

#endif