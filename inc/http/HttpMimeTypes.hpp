#ifndef HTTP_MIME_TYPES_HPP
# define HTTP_MIME_TYPES_HPP

# include <map>
# include <vector>
# include <string>

class HttpMimeTypes
{
	public:
		// --- Constructors and Destructor ---
															HttpMimeTypes(void);
															HttpMimeTypes(const HttpMimeTypes& other);

															~HttpMimeTypes(void);

		// --- Operators Overload ---
		HttpMimeTypes&										operator=(const HttpMimeTypes& rhs);

		// --- Public Methods ---
		//void												addMimeType(HttpMimeType mimeType);

		void												addMimeType(std::string, std::vector<std::string>);
		std::string											getMimeType(const std::string& extension);

	private:
		// --- Private Attributes ---
		//std::vector<HttpMimeType>	mimeTypes_;
		std::map<std::string, std::vector<std::string> >	mimeTypes_;

};

#endif