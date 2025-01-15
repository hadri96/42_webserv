#ifndef CONFIG_PARSER_DIRECTIVE_HPP
# define CONFIG_PARSER_DIRECTIVE_HPP

# include "ConfigParserNode.hpp"

# include <string>
# include <vector>

class	ConfigParserDirective : public ConfigParserNode
{
	public:
		// --- Constructors and Destructor ---
										ConfigParserDirective(void);
										ConfigParserDirective(const ConfigParserDirective& other);

										ConfigParserDirective(const std::string& name, const std::vector<std::string> parameters);

										~ConfigParserDirective(void);

		// --- Operators Overload ---
		ConfigParserDirective&			operator=(const ConfigParserDirective& rhs);

		// --- Public Methods ---
		void							display(void) const;
		void							display(int nestingLevel) const;
};

#endif
