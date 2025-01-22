#ifndef RESOURCE_DEFAULT_HPP
# define RESOURCE_DEFAULT_HPP

# include "Resource.hpp"

class	ResourceDefault : public Resource
{
	public:
		// --- Constructors and Destructor ---
						ResourceDefault(void);

						ResourceDefault(const ResourceDefault& other);
						ResourceDefault(int code);

						~ResourceDefault(void);

		// --- Operators Overload ---
		ResourceDefault&	operator=(const ResourceDefault& rhs);

	private:
		void			createStatusPage(int code);
};

#endif
