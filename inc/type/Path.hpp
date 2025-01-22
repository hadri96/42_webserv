#ifndef PATH_HPP
# define PATH_HPP

# include "PathOrUri.hpp"

class	Path : public PathOrUri
{
	public:
		// --- Constructors and Destructor ---
				Path(void);
				Path(const Path& other);

				Path(const std::string& str);

				~Path(void);

		// --- Operators Overload ---
		Path&	operator=(const Path& rhs);
};

#endif