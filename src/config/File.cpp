#include "File.hpp"
#include <iostream>


// =============================================================================
// Constructors and Destructor
// =============================================================================

File::File(void)
{}

File::File(const File& other)
{
	(void) other;
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
	std::string         line;
    std::string         content;
    std::ifstream       fileStream(path_.getAbsPath().c_str());

    if (fileStream.is_open())
        Logger::logger()->log(LOG_INFO, "File opened: " + path_.getAbsPath());
    while (std::getline(fileStream, line))
        content.append(line, 0, line.length());
    fileStream.close();
	return (content);
}

const Path&	File::getPath(void) const
{
	return (path_);
}