#ifndef CONFIG_LEXER_HPP
# define CONFIG_LEXER_HPP

# include <string>
# include <vector>

enum	ConfigTokenType
{
	CT_KEYWORD,
	CT_LEFT_BRACE,
	CT_RIGHT_BRACE,
	CT_SEMICOLON,
	CT_UNKNOWN
};

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

			// --- Setters and Getters ---
		ConfigTokenType				getType(void) const;
		const std::string&			getValue(void) const;


	private:
		// --- Private Attributes ---
		ConfigTokenType 			type_;
		std::string					value_;
};

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
