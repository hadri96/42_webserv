#ifndef HTTP_HttpHeader_HPP
# define HTTP_HttpHeader_HPP

# include "HttpConnectionType.hpp"
# include "HttpMimeType.hpp"

# include <string>

class	HttpHeader
{
	public:
		// --- Constructors and Destructor ---
		HttpHeader(void);
		HttpHeader(const HttpHeader& other);
		~HttpHeader(void);

		// --- Operators Overload ---
		HttpHeader&		operator=(const HttpHeader& other);

        // --- Public Methods ---
        std::string             generateHttpHeaderString() const;

        // --- Getters ---
        const std::string&      getHost() const;
        const std::string&      getUserAgent() const;
        std::size_t             getContentLength() const;
        HttpMimeType            getMimeType() const;
        HttpConnectionType      getConnectionType() const;
        std::string             getConnectionTypeString() const;
        const std::string&      getAccept() const;
        const std::string&      getAcceptEncoding() const;
        const std::string&      getAcceptLanguage() const;

        // --- Setters ---
        void                    setHost(const std::string& host);
        void                    setUserAgent(const std::string& userAgent);
        void                    setContentLength(std::size_t contentLength);
        void                    setMimeType(HttpMimeType contentType);
        void                    setConnectionType(HttpConnectionType connectionType);
        void                    setAccept(const std::string& accept);
        void                    setAcceptEncoding(const std::string& acceptEncoding);
        void                    setAcceptLanguage(const std::string& acceptLanguage);

	private:
        // --- Private Methods ---

		// --- Private Attributes ---
        std::string     		host_; // host and port of the server ( type ???)
        std::string     		userAgent_;

        std::size_t     		contentLength_; // body.size()
        HttpMimeType     		mimeType_; // "text/html" | "text/css" | "image/png" etc.
        HttpConnectionType  	connectionType_; // either CLOSED or KEEP_ALIVE

        std::string     		accept_; // "text/html" | "text/css" | "image/png" etc. 
        std::string     		acceptEncoding_; // encoding format accepted (zip / deflate / gzip)
        std::string     		acceptLanguage_; // preferred language for response (en / fr)

        std::string     		fullHeaderString_;
};

#endif
