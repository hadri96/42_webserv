#ifndef RESOURCE_STATUS_HPP
# define RESOURCE_STATUS_HPP

# include "Resource.hpp"

class	ResourceStatus : public Resource
{
	public:
		// --- Constructors and Destructor ---
						ResourceStatus(void);

						ResourceStatus(const ResourceStatus& other);
						ResourceStatus(int code);

						~ResourceStatus(void);

		// --- Operators Overload ---
		ResourceStatus&	operator=(const ResourceStatus& rhs);

	private:
		void			createStatusPage(int code);
};

#endif
