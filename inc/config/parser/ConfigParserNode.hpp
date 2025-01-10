#ifndef CONFIG_PARSER_NODE_HPP
# define CONFIG_PARSER_NODE_HPP

# include <string>
# include <vector>

class	ConfigParserNode
{
	public:
		virtual								~ConfigParserNode(void) = 0;

		virtual void						display(void) const = 0;
		virtual void						display(int nestingLevel) const = 0;

		virtual std::string					getName(void) const = 0;
		virtual std::vector<std::string>	getParameters(void) const = 0;
};

#endif