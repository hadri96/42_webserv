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

		// --- Getters and Setters ---
		std::vector<Config>&	getConfigs(void);

		// --- Public Methods ---
		void				addRule(const ConfigInterpreterRule& rule);

		Config				interpret(ConfigParserBlock* root); // or getConfig

		void				displayConfigs(void);
	
	private:
		// --- Private Attributes ---
		std::vector<ConfigInterpreterRule>	rules_;

		int									currentConfig_;
		std::vector<Config>					configs_;

		// --- Private Methods ---
		void 				interpret(ConfigParserNode* node, std::vector<std::string>& context);
		void				interpretBlock(ConfigParserNode* node, std::string block, std::vector<std::string>& context);
		void				interpretDirective(ConfigParserNode* node, std::string directive, std::vector<std::string>& context);

		bool				isBlockValidInContext(std::string block, std::vector<std::string>& context);
		bool				isDirectiveValidInContext(std::string directive, std::vector<std::string>& context);

		ConfigInterpreterRule*	getRule(std::vector<std::string>& context);

		bool				checkNumberOfParameters(int has, int must);
		bool				hasHostAndPort(const std::string& host, int port);

		// --- Handlers ---
		void				handleBlock(ConfigParserNode* node);
		void				handleDirective(ConfigParserNode* node, const std::string& parent);

		void				handleServerName(ConfigParserNode* node);
		void				handleListen(ConfigParserNode* node);
		void				handleIndex(ConfigParserNode* node);
		void				handleErrorPage(ConfigParserNode* node);
		void				handleClientMaxBodySize(ConfigParserNode* node, const std::string& parent);
		void				handleReturn(ConfigParserNode* node);

		void				handleRoot(ConfigParserNode* node);
		void				handleAutoIndex(ConfigParserNode* node);
		void				handleDeny(ConfigParserNode* node);
};

#endif
