#ifndef URI_HPP
# define URI_HPP

# include "PathOrUri.hpp"

class	Uri : public PathOrUri
{
	public:
		// --- Constructors and Destructor ---
				Uri(void);
				Uri(const Uri& other);

				~Uri(void);

		// --- Operators Overload ---
		Uri&	operator=(const Uri& rhs);
};

#endif