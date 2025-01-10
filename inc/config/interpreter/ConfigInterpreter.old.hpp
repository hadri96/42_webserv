#ifndef CONFIG_INTERPRETER_HPP
# define CONFIG_INTERPRETER_HPP

# include <map>
# include <vector>
# include <string>

# include "Config.hpp"
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
		Config				interpret(ConfigParserBlock* root); // or getConfig
	
	private:
		// --- Private Attributes ---
		std::vector<Config*>	servers_;

		std::map<std::vector<std::string>, std::vector<std::string> >	validBlocks_;
		std::map<std::vector<std::string>, std::vector<std::string> >	validDirectives_;

		// --- Private Methods ---
		void 				interpret(ConfigParserNode* node, std::vector<std::string>& context);
		void				interpretBlock(ConfigParserNode* node, std::string block, std::vector<std::string>& context);
		void				interpretDirective(ConfigParserNode* node, std::string directive, std::vector<std::string>& context);

		void				addValidItemsToContext(
								std::vector<std::string> context,
								std::vector<std::string> validBlocks,
								std::vector<std::string> validDirectives
							);
		bool				isBlockValidInContext(std::string block, std::vector<std::string>& context);
		bool				isDirectiveValidInContext(std::string directive, std::vector<std::string>& context);

		std::string			getDisplayableContext(std::vector<std::string>& context);

		// --- Handlers ---
		void	handleServerName(ConfigParserNode* node);
		void	handleServerListen(ConfigParserNode* node);
		void	handleServerIndex(ConfigParserNode* node); 
		void	handleServerErrorPage(ConfigParserNode* node);
		void	handleServerClientMaxBodySize(ConfigParserNode* node);
		void	handleServerReturn(ConfigParserNode* node);

		void	handleRouteRoot(ConfigParserNode* node);
		void	handleRouteAutoIndex(ConfigParserNode* node);
		void	handleRouteIndex(ConfigParserNode* node);
		void	handleRouteReturn(ConfigParserNode* node);

		void	handleMethodAllowed(ConfigParserNode* node);
};

#endif

