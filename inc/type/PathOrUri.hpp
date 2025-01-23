#ifndef PATH_OR_URI_HPP
# define PATH_OR_URI_HPP

# include <vector>
# include <string>

class 	Path;
class	Uri;

class	PathOrUri
{
	public:
		// --- Constructors and Destructor ---
									PathOrUri(void);
									PathOrUri(const PathOrUri& other);

									PathOrUri(const std::string& str);

									~PathOrUri(void);

		// --- Operators Overload ---
		PathOrUri&					operator=(const PathOrUri& rhs);
		PathOrUri					operator/(const std::string& rhs);
		PathOrUri					operator/(const PathOrUri& rhs);
		bool						operator==(const PathOrUri& rhs) const;
		bool						operator!=(const PathOrUri& rhs) const;
		// ··· PathOrUri + string ···
		std::string					operator+(const std::string& rhs);

		// ··· Implicit conversion to string ···
									operator std::string() const;
									operator Path() const;
									operator Uri() const;

		// --- Public Methods ---
		PathOrUri					getParent(void) const;

	private:
		// --- Private Attributes ---
		std::vector<std::string>	components_;

		// --- Private Methods ---
		std::vector<std::string>	split(const std::string& str);
};

std::ostream&	operator<<(std::ostream& os, const PathOrUri& object);

// --- string + PathOrUri ---
std::string		operator+(const std::string& lhs, const PathOrUri& object); 
std::string 	operator+(const std::string& lhs, const PathOrUri* object);

#endif