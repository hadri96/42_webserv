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

										ConfigLexer(const std::string& input);

										~ConfigLexer(void);

		// --- Operators Overload ---
		ConfigLexer&					operator=(const ConfigLexer& rhs);

		// --- Setters and Getters ---
		//const std::vector<ConfigToken>&	getTokens(void) const;

		// --- Public Methods ---
		//void							tokenize(const std::string& input);
		ConfigToken						nextToken(void);
		//void							display(void) const;

	private:
		// --- Private Attributes ---
		//std::vector<ConfigToken>		tokens_;
		std::string						input_;
		size_t							position_;

		// --- Private Methods ---
		bool							isKeyword(char c) const;
};

#endif
