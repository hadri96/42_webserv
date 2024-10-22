#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

class HTTPRequest 
{
    public:


    private:
        std::string     method; // GET, POST, PUT, DELETE
        std::string     uri; // (/index.html)
        std::string     body;
        
};


#endif