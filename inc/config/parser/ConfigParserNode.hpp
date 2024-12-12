#ifndef CONFIG_PARSER_NODE_HPP
# define CONFIG_PARSER_NODE_HPP

class	ConfigParserNode
{
	public:
		virtual			~ConfigParserNode(void) = 0;

		virtual void	display(void) const = 0;
		virtual void	display(int nestingLevel) const = 0;
};

#endif