#ifndef HTTP_REDIRECTION_HPP
# define HTTP_REDIRECTION_HPP

# include <ostream>
# include "Uri.hpp"

class	HttpRedirection
{
	public:
		// --- Constructors and Destructor ---
							HttpRedirection(void);
							HttpRedirection(const HttpRedirection& other);

							HttpRedirection(int statusCode, Uri uri);

							~HttpRedirection(void);

		// --- Operators Overload ---
		HttpRedirection&	operator=(const HttpRedirection& rhs);

		// --- Setters and Getters ---
		int					getStatusCode(void) const;
		const Uri&			getUri(void) const;

		void				log(void);

	private:
		// --- Private Attributes ---
		int					statusCode_;
		Uri					uri_;
};

//std::ostream&	operator<<(std::ostream&, HttpRedirection& object);

#endif
