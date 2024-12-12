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