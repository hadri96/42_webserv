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

							Resource(int code);
							Resource(int code, std::string body);
							Resource(int code, File file);

							~Resource(void);

	// --- Operators Overload ---
		Resource&			operator=(const Resource& rhs);

	// --- Public Methods ---
		int					getCode(void);
		const std::string&	getBody(void);

	protected:
	// --- Protected Attributes ---
		int					code_;
		std::string			body_;

};

#endif
