#ifndef HTMLPARSER_HPP
#define HTMLPARSER_HPP

#include "webserv.hpp"

class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();

    void		parse(const std::string &htmlContent); // Method to parse HTML
    std::string	extractCSSUri() const; // Method to extract a single CSS URI
    std::string	getModifiedHTML() const; // Method to get modified HTML

private:
    std::string modifiedHTML; // Store the modified HTML content
};

#endif
