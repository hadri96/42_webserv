#ifndef RESOURCE_HPP
# define RESOURCE_HPP

# include <string>

class	Resource
{
	public:
	// --- Constructors and Destructor ---
							Resource(void);
							Resource(const Resource& other);

							Resource(int code);
							Resource(int code, std::string body);

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
