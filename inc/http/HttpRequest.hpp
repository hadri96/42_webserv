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
        void                    appendRequest(std::string input);
        std::string             generatePrintString();
        
    // ··· "Deep" Getters and utils ···  
        const std::string       getRelativeUri() const;
        HttpMethodType          getMethod() const;

    // ··· Direct getters ···  
        const std::string&      getRawRequest() const;
        const RequestLine&      getRequestLine() const;
        const Header&           getHeader() const;
        const std::string&      getBody() const;
        int                     getBodySize() const;


    private:
    // --- Private Attributes ---
        std::string     rawRequest_;
        
        RequestLine     requestLine_;
        Header          header_;
        // Could use an std::map for all the headers ??
        std::string     body_;

};

#endif