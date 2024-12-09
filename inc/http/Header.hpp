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
        std::string             generateHeaderString() const;

        // --- Getters ---
        const std::string&      getHost() const;
        const std::string&      getUserAgent() const;
        std::size_t             getContentLength() const;
        const std::string&      getContentType() const;
        ConnectionType          getConnectionType() const;
        std::string             getConnectionTypeString() const;
        const std::string&      getAccept() const;
        const std::string&      getAcceptEncoding() const;
        const std::string&      getAcceptLanguage() const;

        // --- Setters ---
        void                    setHost(const std::string& host);
        void                    setUserAgent(const std::string& userAgent);
        void                    setContentLength(std::size_t contentLength);
        void                    setContentType(const std::string& contentType);
        void                    setConnectionType(ConnectionType connectionType);
        void                    setAccept(const std::string& accept);
        void                    setAcceptEncoding(const std::string& acceptEncoding);
        void                    setAcceptLanguage(const std::string& acceptLanguage);

	private:
        // --- Private Methods ---

		// --- Private Attributes ---
        std::string     host_; // host and port of the server ( type ???)
        std::string     userAgent_;

        std::size_t     contentLength_; // body.size()
        std::string     contentType_; // "text/html" | "text/css" | "image/png" etc.
        ConnectionType  connectionType_; // either CLOSED or KEEP_ALIVE

        std::string     accept_; // "text/html" | "text/css" | "image/png" etc. 
        std::string     acceptEncoding_; // encoding format accepted (zip / deflate / gzip)
        std::string     acceptLanguage_; // preferred language for response (en / fr)

        std::string     fullHeaderString_;
};

#endif
