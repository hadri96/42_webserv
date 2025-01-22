#ifndef PATH_OR_URI_HPP
# define PATH_OR_URI_HPP

# include <vector>
# include <string>

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
		bool						operator==(const PathOrUri& rhs);

		// ··· Implicit conversion to string ···
									operator std::string() const;

		// --- Public Methods ---
		PathOrUri					getParent(void) const;

	private:
		// --- Private Attributes ---
		std::vector<std::string>	components_;

		// --- Private Methods ---
		std::vector<std::string>	split(const std::string& str);
};

std::ostream&	operator<<(std::ostream& os, const PathOrUri& object);

#endif