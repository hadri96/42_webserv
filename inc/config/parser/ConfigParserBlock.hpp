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

										ConfigParserBlock(const std::string& block, const std::vector<std::string>& parameters);

										~ConfigParserBlock(void);

		// --- Operators Overload ---
		ConfigParserBlock&				operator=(const ConfigParserBlock& rhs);

		// --- Public Methods ---
		void							addNode(ConfigParserNode& node);

	private:
		// --- Private Attributes ---
		std::string						block_;
		std::vector<std::string>		parameters_;
		std::vector<ConfigParserNode*>	nodes_;
};

#endif
