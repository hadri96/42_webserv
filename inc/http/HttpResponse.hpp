#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <string>

# include "Config.hpp"
# include "Resource.hpp"
# include "ConfigErrorPage.hpp"

class HttpResponse
{
    public:
        // Constructors & Destructor
        				HttpResponse();
        				HttpResponse(Resource* resource);
        				~HttpResponse();

        // Copy Constructor
        				HttpResponse(const HttpResponse& other);

        // Copy Assignment Operator
        HttpResponse& 	operator=(const HttpResponse& other);

        // Public Methods
        std::string 	getFullResponse() const;
        std::string 	getHeaders() const;

    private:
        std::string 	mimeType_;
        std::string 	statusLine_;
        std::string 	headers_;
        std::string 	body_;
        std::string 	fullResponse_;

        void 			composeFullResponse();
};


#endif

/*
https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/