#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "RequestLine.hpp"
# include "Header.hpp"

# include <string>
# include <sstream>

class HttpRequest 
{
    public:
    // --- Constructors and Destructor ---
        HttpRequest();
        ~HttpRequest();

    // --- Public Methods ---
        void                appendRequest(std::string input);
        std::string         generatePrintString();
        
    // ··· Getters and utils ···  
        const std::string&  getRawRequest() const;
        const RequestLine&  getRequestLine() const;
        const Header&       getHeader() const;
        const std::string&  getBody() const;


    private:
    // --- Private Attributes ---
        std::string     rawRequest_; // full unparsed string of the request
        // Not ideal for very long requests, which should be read in chunks rather than saved into memory
        
        RequestLine     requestLine_; // contains httpMethodType, requestTarget(path), HttpVersion
        Header          header_; // contains all header information
        std::string     body_;

};

#endif