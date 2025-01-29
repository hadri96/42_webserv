#ifndef RESOURCE_REDIRECTION_HPP
# define RESOURCE_REDIRECTION_HPP

# include "Resource.hpp"
# include "Uri.hpp"

class	ResourceRedirection : public Resource
{

	public:
		// --- Constructors and Destructor ---
								ResourceRedirection(void);

								ResourceRedirection(const ResourceRedirection& other);
								ResourceRedirection(int code, Uri uri);

								~ResourceRedirection(void);

		// --- Operators Overload ---
		ResourceRedirection&	operator=(const ResourceRedirection& rhs);

		Uri						getUri(void) const;

	private:
		Uri uri_;

};

#endif
