#include "HttpMimeTypes.hpp"
#include "ToVector.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpMimeTypes::HttpMimeTypes(void)
{
    // REVISIT : REPLACE BY A CONFIGURATION FILE ?

    std::string	mimeType1 = "text/html";
	const char* extensions1[] = {"html", "htm", "shtml", 0};

	std::string mimeType2 = "text/css";
	const char* extensions2[] = {"css", 0};

	std::string mimeType3 = "application/javascript";
	const char* extensions3[] = {"js", 0};

	std::string mimeType4 = "image/jpeg";
	const char* extensions4[] = {"jpeg", "jpg", 0};

	std::string mimeType5 = "image/gif";
	const char* extensions5[] = {"gif", 0};

	addMimeType(mimeType1, toVector(extensions1));
	addMimeType(mimeType2, toVector(extensions2));
	addMimeType(mimeType3, toVector(extensions3));
	addMimeType(mimeType4, toVector(extensions4));
	addMimeType(mimeType5, toVector(extensions5));

}

HttpMimeTypes::HttpMimeTypes(const HttpMimeTypes& other) :
    mimeTypes_(other.mimeTypes_)
{}

HttpMimeTypes::~HttpMimeTypes(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpMimeTypes& HttpMimeTypes::operator=(const HttpMimeTypes& rhs)
{
    if (this == &rhs)
        return (*this);

    mimeTypes_ = rhs.mimeTypes_;

    return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

void HttpMimeTypes::addMimeType(const std::string mimeType, std::vector<std::string> extensions)
{
    mimeTypes_[mimeType] = extensions;
}

std::string HttpMimeTypes::getMimeType(const std::string& extension)
{
    for (std::map<std::string, std::vector<std::string> >::iterator it = mimeTypes_.begin();
        it != mimeTypes_.end(); ++it)
    {
        for (size_t i = 0; i != it->second.size(); ++i)
        {
            if (it->second[i] == extension)
                return (it->first);
        }
    }
    return ("application/octet-stream");
}