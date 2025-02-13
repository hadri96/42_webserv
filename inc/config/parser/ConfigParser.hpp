#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

# include "ConfigLexer.hpp"
# include "ConfigParserBlock.hpp"

# include <vector>

class	ConfigParser
{
	public:
		// --- Constructors and Destructor ---
							ConfigParser(void);
							ConfigParser(const ConfigParser& other);

							ConfigParser(const std::string& input);

							~ConfigParser(void);

		// --- Operators Overload ---
		ConfigParser&		operator=(const ConfigParser& rhs);

		// --- Setters and Getters ---
		ConfigParserBlock*	getRoot(void) const;

		// --- Public Methods ---
		void				parse(void);
		void				display(void);
		void				destroy(void);
	
	private:
		// --- Private Attributes ---
		ConfigParserBlock*	root_;
		ConfigLexer*		lexer_;
		ConfigToken			currentToken_;

		// --- Private Methods ---
		void				consume(ConfigTokenType expectedToken);

		void				parseBlock(ConfigParserBlock* parent, int openBlocks);

		void				parseBlock(
								const std::vector<ConfigToken>& tokens,
								ConfigParserBlock* parent,
								size_t& index);

		void				displayBlock(ConfigParserBlock* block);
};

#endif
