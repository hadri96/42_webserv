#ifndef CONFIG_PARSER_NODE_HPP
# define CONFIG_PARSER_NODE_HPP

# include <string>
# include <vector>

class	ConfigParserNode
{
	protected:
		std::string							name_;
		std::vector<std::string>			parameters_;

	public:
		// --- Constructors and Destructor ---
											ConfigParserNode(void);
											ConfigParserNode(const std::string& name);
											ConfigParserNode(const std::string& name, const std::vector<std::string>& parameters);
		virtual								~ConfigParserNode(void) = 0;

		// --- Public Methods ---
		std::string							getName(void) const;
		std::vector<std::string>			getParameters(void) const;

		virtual void						display(void) const = 0;
		virtual void						display(int nestingLevel) const = 0;
};

#endif