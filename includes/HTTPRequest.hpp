#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

class HTTPRequest 
{
    public:
    // --- Constructors and Destructor ---
        HTTPRequest();
        ~HTTPRequest();

    // --- Public Methods ---
        void            appendRequest(std::string input);
        
        // ··· Getters and utils ···  
        std::string     getRawRequest();


    private:
    // --- Private Attributes ---
        std::string     method; // GET, POST, PUT, DELETE
        std::string     uri; // (/index.html)
        std::string     body;
        std::string     rawRequest; // full unparsed string of the request
};

#endif