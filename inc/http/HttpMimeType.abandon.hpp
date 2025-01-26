#ifndef HTTP_MIME_TYPE_HPP
# define HTTP_MIME_TYPE_HPP

# include <vector>
# include <string>

class HttpMimeType
{
	public:
		// --- Constructors and Destructor ---
									HttpMimeType(void);
									HttpMimeType(const HttpMimeType& other);

									HttpMimeType(const std::string& type, std::vector<std::string> extensions);

									~HttpMimeType(void);

		// --- Operators Overload ---
		HttpMimeType&               operator=(const HttpMimeType& rhs);

		// --- Public Methods ---
		bool						definesExtension(const std::string& extension);

	private:
		// --- Private Attributes ---
		std::string					mimeType_;
		std::vector<std::string>	extensions_;

};

#endif