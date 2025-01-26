#include "HttpMimeType.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

HttpMimeType::HttpMimeType(void)
{}

HttpMimeType::HttpMimeType(const HttpMimeType& other)
{}

HttpMimeType::HttpMimeType(const std::string& mimeType, std::vector<std::string> extensions) :
    mimeType_ = mimeType,
    extensions_ = extensions
{}

HttpMimeType::~HttpMimeType(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

HttpMimeType& HttpMimeType::operator=(const HttpMimeType& rhs)
{
    if (this == &rhs)
        return (*this);

    mimeType_ = rhs.type_;
    extensions_ = rhs.extensions_;

    return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================


bool HttpMimeType::definesExtension(const std::string& extension)
{
    for (size_t i = 0; i != extensions_.size(); ++i)
    {
        if (extensions_[i] == extension)
            return (true);
    }
    return (false);
}