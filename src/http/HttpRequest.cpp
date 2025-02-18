#include "HttpRequest.hpp"
#include "ToString.hpp"
#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpRequest::HttpRequest() : 
    rawRequest_(),
    //"GET /cgi-bin/hello.php?name=newFileMickey&content=donaldDucknotdonaldTrump HTTP/1.1\r\n Host: http://127.0.0.1:7777/\r\n Connection: close\r\n\r\n"),
    requestLine_(HttpRequestLine()),
    body_("")
{
    // inputs_.insert(std::make_pair("name", "newFileMickey")); // REVISIT : ?
    // inputs_.insert(std::make_pair("content", "donaldDuck not donaldTrump")); // REVISIT : ?
}

HttpRequest::HttpRequest(const HttpRequest& other) :
	rawRequest_(other.rawRequest_),
	requestLine_(other.requestLine_),
	headers_(other.headers_),
	inputs_(other.inputs_),
	body_(other.body_)
{}

HttpRequest::~HttpRequest() {}

void    HttpRequest::appendRequest(std::string input)
{
    if (rawRequest_.empty())
        rawRequest_ = input;
    else 
        rawRequest_.append(input, 0, input.length());
}

// =============================================================================
// Operators Overload
// =============================================================================

HttpRequest&	HttpRequest::operator=(const HttpRequest& rhs)
{
	if (this == &rhs)
		return (*this);

	rawRequest_ = rhs.rawRequest_;
	requestLine_ = rhs.requestLine_;
	headers_ = rhs.headers_;
	inputs_ = rhs.inputs_;
	body_ = rhs.body_;

	return (*this);
}

// =============================================================================
// Getters & Setters
// =============================================================================

const std::string& HttpRequest::getRawRequest() const 
{
    return (rawRequest_);
}

void	HttpRequest::setRawRequest(const std::string& rawRequest)
{
	rawRequest_ = rawRequest;
}

void HttpRequest::setInputsGet(std::string& queryString)
{
    inputs_.clear();

    std::string                 key;
    std::string                 value;
    std::string::size_type      pos = 0;
    std::string::size_type      ampPos;
    std::string::size_type      eqPos;

    while (pos < queryString.length())
    {
        ampPos = queryString.find('&', pos);
        if (ampPos == std::string::npos)
            ampPos = queryString.length();

        eqPos = queryString.find('=', pos);
        
        if (eqPos != std::string::npos && eqPos < ampPos)
        {
            key = queryString.substr(pos, eqPos - pos);
            value = queryString.substr(eqPos + 1, ampPos - eqPos - 1);
        }
        else
        {
            key = queryString.substr(pos, ampPos - pos);
            value = "";
        }

        if (!key.empty())
            inputs_[key] = value;

        pos = ampPos + 1;
    }
}

void    HttpRequest::setInputsPost(std::map<std::string, std::string> parsedData)
{
    inputs_.clear();
    inputs_ = parsedData;
}

// ·············································································
// Request Line
// ·············································································

// --- Method ---

HttpMethodType    HttpRequest::getMethod() const
{
    return (requestLine_.getMethod());
}

void    HttpRequest::setMethod(HttpMethodType httpMethod)
{
    requestLine_.setMethod(httpMethod);
}

// --- Uri ---

const Uri& HttpRequest::getUri() const
{
    return (requestLine_.getUri());
}

void	HttpRequest::setUri(Uri uri)
{
    requestLine_.setUri(uri);
}

// --- Query string ---

const std::string&  HttpRequest::getQueryString() const
{
    return (requestLine_.getQueryString());
}

void  HttpRequest::setQueryString(const std::string queryString)
{
    return (requestLine_.setQueryString(queryString));
}

// --- Http Version ---

const std::string&  HttpRequest::getHttpVersion(void) const
{
    return(requestLine_.getHttpVersion());
}

void    HttpRequest::setHttpVersion(const std::string& httpVersion)
{
    requestLine_.setHttpVersion(httpVersion);
}

// ·············································································
// Header
// ·············································································


// ·············································································
// Body
// ·············································································

const std::string& HttpRequest::getBody() const 
{
    return (body_);
}

void    HttpRequest::setBody(const std::string& body)
{
    body_ = body;
}

int HttpRequest::getBodySize() const 
{
    return (body_.length() * sizeof(char));
}

std::string HttpRequest::getInput(std::string key)
{
    return (inputs_[key]);
}

void    HttpRequest::setHeader(std::string key, std::string value)
{
    headers_[key] = value;
}

std::string HttpRequest::getHeader(std::string key)
{
    return (headers_[key]);
}

// ··· "Deep" Getters and utils ···


// =============================================================================
// Public Methods 
// =============================================================================

void        HttpRequest::log()
{
    Logger::logger()->log(LOG_DEBUG, "method : " + toString(requestLine_.getMethod()));
	Logger::logger()->log(LOG_DEBUG, "uri : " + requestLine_.getUri());
	Logger::logger()->log(LOG_DEBUG, "version : " + requestLine_.getHttpVersion());

    if (headers_.empty())
        Logger::logger()->log(LOG_DEBUG, "headers empty !!!");

    std::string             headersLog = "headers : \n";
    std::map<std::string, std::string>::const_iterator      it;

    for (it = headers_.begin(); it != headers_.end(); ++it)
        headersLog += "  " + it->first + " : " + it->second + "\n";

    Logger::logger()->log(LOG_DEBUG, headersLog);

    std::string             inputsLog = "inputs : \n";

    for (it = inputs_.begin(); it != inputs_.end(); ++it)
        inputsLog += "  " + it->first + " : " + it->second + "\n";

    Logger::logger()->log(LOG_DEBUG, inputsLog);
}