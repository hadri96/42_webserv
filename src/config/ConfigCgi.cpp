#include "ConfigCgi.hpp"

// =============================================================================
// Constructors and Destructor
// =============================================================================

ConfigCgi::ConfigCgi(void)
{}

ConfigCgi::ConfigCgi(const ConfigCgi& other) :
	extensions_(other.extensions_),
	executable_(other.executable_),
	parameters_(other.parameters_)
{}

ConfigCgi::~ConfigCgi()
{}

// =============================================================================
// Operators Overload
// =============================================================================

ConfigCgi&	ConfigCgi::operator=(const ConfigCgi& rhs)
{
	if (this == &rhs)
		return (*this);

	extensions_ = rhs.extensions_;
	executable_ = rhs.executable_;
	parameters_ = rhs.parameters_;

	return (*this);
}

// =============================================================================
// Setters and Getters
// =============================================================================

// --- Setters ---
void	ConfigCgi::setExecutable(Path executable)
{
	executable_ = executable;
}

void	ConfigCgi::setParameters(const std::string& parameters)
{
	parameters_ = parameters;
}

void	ConfigCgi::addExtension(const std::string& extension)
{
	extensions_.push_back(extension);
}

// --- Getters ---
Path	ConfigCgi::getExecutable(void) const
{
	return (executable_);
}

std::string	ConfigCgi::getParameters(void) const
{
	return (parameters_);
}

std::vector<std::string> ConfigCgi::getExtensions(void) const
{
	return (extensions_);
}

#include <iostream>
bool	ConfigCgi::hasExtension(const std::string& extension)
{
	for (size_t i = 0; i != extensions_.size(); ++i)
	{
		if (extensions_[i] == extension)
			return (true);
	}
	return (false);
}