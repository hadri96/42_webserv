#include "webserv.hpp"

HTMLParser::HTMLParser() {}

HTMLParser::~HTMLParser() {}

void HTMLParser::parse(const std::string &htmlContent)
{
    modifiedHTML = htmlContent; // Start with the original HTML content
}

std::string HTMLParser::extractCSSUri() const
{
    std::string::size_type pos = 0;

    // Extract the first <link> tag for an external stylesheet
    while ((pos = modifiedHTML.find("<link", pos)) != std::string::npos)
    {
        std::string::size_type hrefPos = modifiedHTML.find("href=\"", pos);
        if (hrefPos != std::string::npos)
        {
            hrefPos += 6; // Move past 'href="'
            std::string::size_type endQuote = modifiedHTML.find("\"", hrefPos);
            if (endQuote != std::string::npos)
            {
                return modifiedHTML.substr(hrefPos, endQuote - hrefPos); // Return the first CSS URI found
            }
        }
        pos++;
    }

    return ""; // Return an empty string if no CSS URI is found
}

std::string HTMLParser::getModifiedHTML() const
{
    return modifiedHTML; // Return the modified HTML content
}
