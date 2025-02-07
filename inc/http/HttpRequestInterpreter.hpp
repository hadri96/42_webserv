#ifndef HTTP_REQUEST_INTERPRETER_HPP
# define HTTP_REQUEST_INTERPRETER_HPP

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include "Server.hpp"
# include "Config.hpp"

class HttpRequestInterpreter 
{
    public:
    // --- Constructors and Destructor ---
        HttpRequestInterpreter(Server* server);
        ~HttpRequestInterpreter();

    // --- Public Methods ---
        HttpResponse    interpret(HttpRequest& request, Config& config);
        
    private:
    // --- Private Attributes ---
        Server*     server_;

    // --- Private Methods ---
         // --- Method Handlers ---
        HttpResponse    handleGetRequest(Config& config, HttpRequest& request);
        HttpResponse    handlePostRequest(Config& config, HttpRequest& request);
        HttpResponse    handleDeleteRequest(Config& config, HttpRequest& request);

        // --- Resources ---
		Resource*		createResourceFile(Config& config, HttpRequest& request); // GET (CGI ou autre)
		Resource*		createResourceError(Config& config, int code); // -> creer custom Error
		Resource*		createResourceDirectory(Config& config, HttpRequest& request);
        Resource*       createResourceCgi(Config& config, HttpRequest& request);
		Resource*		createResourceRedirection(Config& config, HttpRequest& request);

        // --- Utils ---
        bool            fileInServer(std::string uri, Config& config);
        bool            isCgiRequest(Config& config, HttpRequest& request);
        char**          prepareCgiEnvironment(Config& config, HttpRequest& request);
        bool            isValidToken(std::string token);

};

#endif
