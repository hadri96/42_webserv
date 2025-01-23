#ifndef CONFIG_REDIRECTION_HPP
# define CONFIG_REDIRECTION_HPP

# include <ostream>
# include "Uri.hpp"

class	ConfigRedirection
{
	public:
		// --- Constructors and Destructor ---
							ConfigRedirection(void);
							ConfigRedirection(const ConfigRedirection& other);

							ConfigRedirection(int statusCode, Uri uri);

							~ConfigRedirection(void);

		// --- Operators Overload ---
		ConfigRedirection&	operator=(const ConfigRedirection& rhs);

		// --- Setters and Getters ---
		int					getStatusCode(void) const;
		const Uri&			getUri(void) const;

		void				log(void);

	private:
		// --- Private Attributes ---
		int					statusCode_;
		Uri					uri_;
};

//std::ostream&	operator<<(std::ostream&, ConfigRedirection& object);

#endif
