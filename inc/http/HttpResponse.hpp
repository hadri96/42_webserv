#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

# include <string>

# include "Config.hpp"
# include "Resource.hpp"
# include "ConfigErrorPage.hpp"

class HttpResponse
{
	public:
		// --- Constructors and Destructor ---
						HttpResponse();

						HttpResponse(Resource* resource);

						~HttpResponse();

		// --- Public Methods ---
		// ··· Getters and utils ···  
		std::string		getFullResponse() const;
		std::string		getHeaders() const;
	
	private:
		// --- Private Attributes ---
		std::string		mimeType_;
		std::string     statusLine_;
		std::string     headers_;
		std::string     body_;
		std::string     fullResponse_;

		// --- Private Methods ---
		void			composeFullResponse();
};

#endif

/*
https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/