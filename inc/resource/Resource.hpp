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

		virtual				~Resource(void);

	// --- Operators Overload ---
		Resource&			operator=(const Resource& rhs);

	// --- Public Methods ---
		int					getCode(void);
		const std::string&	getBody(void);

		std::string			getMimeType(void) const;
		void				setMimeType(std::string mimeType);

		void				setStatusLine(const std::string& statusLine);

	protected:
	// --- Protected Attributes ---
		int					code_;
		std::string			statusLine_;
		std::string			mimeType_;
		std::string			body_;

};

#endif
