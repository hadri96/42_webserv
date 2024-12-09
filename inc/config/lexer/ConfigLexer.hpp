#ifndef CONFIG_LEXER_HPP
# define CONFIG_LEXER_HPP

# include "ConfigToken.hpp"

# include <string>
# include <vector>

class	ConfigLexer
{
	public:
		// --- Constructors and Destructor ---
									ConfigLexer(void);
									ConfigLexer(const ConfigLexer& other);

									~ConfigLexer(void);

		// --- Operators Overload ---
		ConfigLexer&				operator=(const ConfigLexer& rhs);

		// --- Public Methods ---
		std::vector<ConfigToken>	tokenize(const std::string& input);
		void						displayTokens(std::vector<ConfigToken> tokens);

	private:
		// --- Private Methods ---
		bool						isKeyword(char c);
};

#endif
