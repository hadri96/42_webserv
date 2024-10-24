#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

class HTTPRequest 
{
    public:
        //constructors // destructors 
        HTTPRequest();
        ~HTTPRequest();

        //methods 
        void            appendRequest(std::string input);
        std::string     getRawRequest();


    private:
        std::string     method; // GET, POST, PUT, DELETE
        std::string     uri; // (/index.html)
        std::string     body;
        std::string     rawRequest; // full unparsed string of the request
        
};


#endif