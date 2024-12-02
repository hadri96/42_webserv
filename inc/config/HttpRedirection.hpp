#ifndef HTTP_REDIRECTION_HPP
# define HTTP_REDIRECTION_HPP

# include "Path.hpp"

class	HttpRedirection
{
	public:
		// --- Constructors and Destructor ---
							HttpRedirection(void);
							HttpRedirection(const HttpRedirection& other);

							HttpRedirection(int statusCode, const Path& path);

							~HttpRedirection(void);

		// --- Operators Overload ---
		HttpRedirection&	operator=(const HttpRedirection& rhs);

		// --- Setters and Getters ---
		int					getStatusCode(void) const;
		const Path&			getPath(void) const;

	private:
		// --- Private Attributes ---
		int					statusCode_;
		Path				path_;
};

#endif
