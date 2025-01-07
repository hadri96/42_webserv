#ifndef CONFIG_INTERPRETER_HPP
# define CONFIG_INTERPRETER_HPP

# include "Config.hpp"
# include "ConfigInterpreterRule.hpp"
# include "ConfigParserBlock.hpp"

class	ConfigInterpreter
{
	public:
		// --- Constructors and Destructor ---
							ConfigInterpreter(void);
							ConfigInterpreter(const ConfigInterpreter& other);

							~ConfigInterpreter(void);

		// --- Operators Overload ---
		ConfigInterpreter&	operator=(const ConfigInterpreter& rhs);

		// --- Public Methods ---
		void					addRule(const ConfigInterpreterRule& rule);

		Config				interpret(ConfigParserBlock* root); // or getConfig
	
	private:
		// --- Private Attributes ---
		std::vector<ConfigInterpreterRule>	rules_;
		//std::vector<Config*>					servers_;

		// --- Private Methods ---
		void 				interpret(ConfigParserNode* node, std::vector<std::string>& context);
		void				interpretBlock(ConfigParserNode* node, std::string block, std::vector<std::string>& context);
		void				interpretDirective(ConfigParserNode* node, std::string directive, std::vector<std::string>& context);

		bool				isBlockValidInContext(std::string block, std::vector<std::string>& context);
		bool				isDirectiveValidInContext(std::string directive, std::vector<std::string>& context);

		ConfigInterpreterRule*	getRule(std::vector<std::string>& context);

		// --- Handlers ---
		void				handleServerName(ConfigParserNode* node);
		void				handleListen(ConfigParserNode* node);
		void				handleIndex(ConfigParserNode* node);
		void				handleErrorPage(ConfigParserNode* node);
		void				handleClientMaxBodySize(ConfigParserNode* node);
		void				handleReturn(ConfigParserNode* node);
};

#endif
