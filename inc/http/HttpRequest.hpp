#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "RequestLine.hpp"
# include "Header.hpp"

# include <string>
# include <sstream>
# include <map>

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
        const Uri&              getUri() const;


    private:
    // --- Private Attributes ---
        std::string                         rawRequest_;

        RequestLine                         requestLine_;
        Header                              header_;
        std::string                         body_;
        // std::map<std::string, std::string>  inputs_; // need to get values from parsing 
};

#endif