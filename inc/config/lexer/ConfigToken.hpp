#ifndef CONFIG_TOKEN_HPP
# define CONFIG_TOKEN_HPP

# include "ConfigTokenType.hpp"

# include <string>

class	ConfigToken
{
	public:
		// --- Constructors and Destructor ---
									ConfigToken(void);
									ConfigToken(const ConfigToken& other);

									ConfigToken(ConfigTokenType type, const std::string& value);

									~ConfigToken(void);

		// --- Operators Overload ---
		ConfigToken&				operator=(const ConfigToken& rhs);

		bool						operator==(ConfigTokenType rhs);
		bool						operator!=(ConfigTokenType rhs);

		// --- Setters and Getters ---
		ConfigTokenType				getType(void) const;
		const std::string&			getValue(void) const;


	private:
		// --- Private Attributes ---
		ConfigTokenType 			type_;
		std::string					value_;
};

#endif