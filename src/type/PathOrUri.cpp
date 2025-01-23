#include "PathOrUri.hpp"
#include <sstream>

// =============================================================================
// Constructors and Destructor
// =============================================================================

PathOrUri::PathOrUri(void)
{}

PathOrUri::PathOrUri(const PathOrUri& other) :
	components_(other.components_)
{}

PathOrUri::PathOrUri(const std::string& str) :
	components_(split(str))
{}

PathOrUri::~PathOrUri(void)
{}

// =============================================================================
// Operators Overload
// =============================================================================

// --- Assignment operator ---
PathOrUri&	PathOrUri::operator=(const PathOrUri& rhs)
{
	if (this == &rhs)
		return (*this);
	
	components_ = rhs.components_;
	return (*this);
}

// --- Implicit conversion to string ---
PathOrUri::operator std::string() const
{
	std::string str = "/";

	for (size_t i = 0; i != components_.size(); ++i)
	{
		str.append(components_[i]);
		if (i != components_.size() - 1)
			str.append("/");
	}
	return (str);
}

// --- Ostream ---
std::ostream&	operator<<(std::ostream& os, const PathOrUri& object)
{
	std::string str = object;
	os << str;

	return (os);
}

// --- Append a string ---
PathOrUri	PathOrUri::operator/(const std::string& rhs)
{
	PathOrUri suffix(rhs);
	return (*this / suffix);
}


// --- Append a PathOrUri ---
PathOrUri	PathOrUri::operator/(const PathOrUri& rhs)
{
	PathOrUri newPathOrUri(*this);

	newPathOrUri.components_.insert(newPathOrUri.components_.end(), rhs.components_.begin(), rhs.components_.end());
	return (newPathOrUri);
}

// --- Boolean ---
bool	PathOrUri::operator==(const PathOrUri& rhs) const
{
	return (components_ == rhs.components_);
}

bool	PathOrUri::operator!=(const PathOrUri& rhs) const
{
	return (components_ != rhs.components_);
}


// --- PathOrUri + string ---
std::string	PathOrUri::operator+(const std::string& rhs)
{
	std::string lhs = *this;
	return (lhs + rhs);
}

// --- string + PathOrUri ---
std::string		operator+(const std::string& lhs, const PathOrUri& object)
{
	std::string rhs = object;
	return (lhs + rhs);
}

// --- string + PathOrUri* ---
std::string operator+(const std::string& lhs, const PathOrUri* object)
{
	std::string rhs = *object;
	return (lhs + rhs);
}

// =============================================================================
// Public Methods
// =============================================================================

PathOrUri	PathOrUri::getParent(void) const
{
	PathOrUri parent(*this);

	if (components_.empty())
		return (PathOrUri("/"));
	parent.components_.pop_back();
	return (parent);
}

// =============================================================================
// Private Methods
// =============================================================================

std::vector<std::string> PathOrUri::split(const std::string& str)
{
	std::istringstream stream(str);
	std::string part;
	char delimiter = '/';
	std::vector<std::string> components;

	while (std::getline(stream, part, delimiter))
	{
		if (!part.empty() && part != ".") // Skip empty parts and "."
			components.push_back(part);
	}

	return (components);
}