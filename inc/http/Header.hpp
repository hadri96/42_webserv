#ifndef HEADER_HPP
# define HEADER_HPP

# include "ConnectionType.hpp"

# include <string>

class	Header
{
	public:
		// --- Constructors and Destructor ---
		Header(void);
		Header(const Header& other);
		~Header(void);

		// --- Operators Overload ---
		Header&		operator=(const Header& other);

        // --- Public Methods ---

	private:
		// --- Private Attributes ---
        std::string     host_; // host and port of the server ( type ???)
        std::string     userAgent_;

        std::size_t     contentLength_; // body.size()
        std::string     contentType_; // "text/html" | "text/css" | "image/png" etc.
        connectionType  connectionType_; // either CLOSED or KEEP_ALIVE

        std::string     accept_; // "text/html" | "text/css" | "image/png" etc. 
        std::string     acceptEncoding_; // encoding format accepted (zip / deflate / gzip)
        std::string     acceptLanguage_; // preferred language for response (en / fr)
};

#endif
