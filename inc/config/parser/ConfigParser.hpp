#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

# include "ConfigLexer.hpp"

# include <vector>

class	ConfigParser
{
	public:
		// --- Constructors and Destructor ---
						ConfigParser(void);
						ConfigParser(const ConfigParser& other);

						~ConfigParser(void);

		// --- Operators Overload ---
		ConfigParser&	operator=(const ConfigParser& rhs);

		// --- Public Methods ---
		void			parse(std::vector<ConfigToken>& tokens);
	
	private:
		// --- Private Methods ---
		void			ConfigParser::parseBlock(std::vector<ConfigToken>& tokens, ConfigParserBlock* parent, size_t& index)
};

#endif
