#ifndef URI_HPP
# define URI_HPP

# include <string>
# include <vector>

class	Uri
{
	public:
		// --- Constructors and Destructor ---
							Uri(void);
							Uri(const Uri& other);
							Uri(const std::string& uri);
							~Uri(void);
		// --- Operators Overload ---
		Uri&				operator=(const Uri& rhs);
		bool				operator==(const Uri& rhs) const;

		// --- Getters and Setters ---
		const std::string&	getUri(void) const;

		// getLevel

	private:
		// --- Private Attributes ---
		std::string			uri_;
		// std::vector<std::string>	chunks_;
};

#endif