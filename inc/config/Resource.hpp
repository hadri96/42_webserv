#ifndef RESOURCE_HPP
# define RESOURCE_HPP

# include <string>
# include "File.hpp"

class	Resource
{
	public:
	// --- Constructors and Destructor ---
					Resource(void);
					Resource(const Resource& other);

					Resource(int code, std::string body);
					Resource(int code, File file);

					~Resource(void);

	// --- Operators Overload ---
		Resource&	operator=(const Resource& rhs);

	// --- Protected Methods ---
	protected:
		int			code_;
		std::string	body_;
};

#endif
