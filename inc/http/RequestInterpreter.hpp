#ifndef REQUESTINTERPRETER_HPP
# define REQUESTINTERPRETER_HPP

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include "Server.hpp"

class RequestInterpreter 
{
    public:
    // --- Constructors and Destructor ---
        RequestInterpreter(Server* server);
        ~RequestInterpreter();

    // --- Public Methods ---
        void        interpret(HttpRequest& request);
        
    // ··· Getters and utils ···  


    // ··· Exceptions ···  
        class BadRequest : public std::exception
        {
            public:
                const char  *what() const throw()
                {
                    return ("Bad Request (400)");
                };
        };


    private:
    // --- Private Attributes ---
        Server*     server_;

    // --- Private Methods ---
        bool        fileInServer(std::string uri);
};

#endif

/*

Responsibilities:

    1. Routing 
        - static file ?
        - CGI ? 
        - 
    2. Request validation:
        - valid Method?
        - checks for request syntax / semantics
    3. 


*/