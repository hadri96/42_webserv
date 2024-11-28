#include "Cgi.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

Cgi::Cgi(void) :
	fileExtension_(".php"),
	rootPath_(),
	scriptPath_(),
	workingDirectory_()
{}

Cgi::Cgi(const Cgi& other) :
	fileExtension_(other.fileExtension_),
	rootPath_(other.rootPath_),
	scriptPath_(other.scriptPath_),
	workingDirectory_(other.workingDirectory_)
{}

Cgi::~Cgi()
{}

// =============================================================================
// Operators Overload
// =============================================================================

Cgi&	Cgi::operator=(const Cgi& rhs)
{
	if (this == &rhs)
		return (*this);

	fileExtension_ = rhs.fileExtension_;
	rootPath_ = rhs.rootPath_;
	scriptPath_ = rhs.scriptPath_;
	workingDirectory_ = rhs.workingDirectory_;

	return (*this);
}
