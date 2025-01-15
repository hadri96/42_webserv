#ifndef CONFIG_PARSER_BLOCK_HPP
# define CONFIG_PARSER_BLOCK_HPP

# include "ConfigParserNode.hpp"

# include <string>
# include <vector>

class	ConfigParserBlock : public ConfigParserNode
{
	public:
		// --- Constructors and Destructor ---
												ConfigParserBlock(void);
												ConfigParserBlock(const ConfigParserBlock& other);

												ConfigParserBlock(const std::string& name, const std::vector<std::string> parameters);

												~ConfigParserBlock(void);

		// --- Operators Overload ---
		ConfigParserBlock&						operator=(const ConfigParserBlock& rhs);

		// --- Setters and Getters ---
		const std::vector<ConfigParserNode*>&	getNodes(void) const;

		// --- Public Methods ---
		void									addNode(ConfigParserNode* node);
		void									display(void) const;

	private:
		// --- Private Attributes ---
		std::vector<ConfigParserNode*>			nodes_;

		// --- Private Methods ---
		void									display(ConfigParserNode* node) const;
		void									display(int nestingLevel) const;
};

#endif
