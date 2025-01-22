#include "File.hpp"
#include "ToString.hpp"
#include <iostream>

#include "Logger.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

File::File(void)
{}

File::File(const File& other) :
	path_(other.path_),
	content_(other.content_)
{
	//if (!other.path_.getPath().empty())
	std::string pathStr = other.path_;
    file_.open(pathStr.c_str());
}

// Hardcoded for testing purposes: 
File::File(const int errorCode)
{
	std::string	filename = "/" + toString(errorCode) + ".html";
	// Hardcoded for testing purposes
	path_ = Path("/www/errors" + filename);
}

File::File(const std::string& filename)
{
	file_.open(filename.c_str());

	if (!file_.is_open())
		throw std::runtime_error("File could not be opened");
}

File::File(const Path& path) : path_(path) {}

File::~File(void)
{
	file_.close();
}

// =============================================================================
// Operators Overload
// =============================================================================

File&	File::operator=(const File& rhs)
{
	(void) rhs;
	return (*this);
}

// =============================================================================
// Public Methods
// =============================================================================

void	File::setContent(void)
{
	std::string	line;
	while (std::getline(file_, line))
	{
		content_ += line + '\n';
	}
}

const std::string&	File::getContent(void) const
{
	return (content_);
}

std::string	File::read(void) const
{
	Logger::logger()->log(LOG_DEBUG, "Abs Path in file reader : " + path_.getAbsPath());

	std::string         line;
    std::string         content;

	std::string			absPath = path_.getAbsPath();
    std::ifstream       fileStream(absPath.c_str());

    if (fileStream.is_open())
        Logger::logger()->log(LOG_INFO, "File opened: " + path_.getAbsPath());
    while (std::getline(fileStream, line))
        content.append(line, 0, line.length());
    fileStream.close();
	return (content);
}

const Path	File::getPath(void) const
{
	return (path_);
}