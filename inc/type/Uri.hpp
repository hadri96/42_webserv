#ifndef URI_HPP
# define URI_HPP

# include "PathOrUri.hpp"

class	Uri : public PathOrUri
{
	public:
		// --- Constructors and Destructor ---
				Uri(void);
				Uri(const Uri& other);

				Uri(const std::string& str);

				~Uri(void);

		// --- Operators Overload ---
		Uri&	operator=(const Uri& rhs);

		// --- Public Methods ---
		Uri		getParent(void) const;
		bool	matchAnyParent(const Uri& rhs);
};

#endif
