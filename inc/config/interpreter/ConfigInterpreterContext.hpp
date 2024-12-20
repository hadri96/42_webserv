#ifndef CONFIG_INTERPRETER_CONTEXT_HPP
# define CONFIG_INTERPRETER_CONTEXT_HPP

# include "ConfigParserNode.hpp"
# include "ConfigInterpreter.hpp"

# include <vector>
# include <string>

class	ConfigInterpreterContext
{
	public:
		// --- Constructors and Destructor ---
													ConfigInterpreterContext(void);
													ConfigInterpreterContext(const ConfigInterpreterContext& other);

													ConfigInterpreterContext(
														const char* context[], 
														const char* validBlocks[],
														const char* validDirectives[],
														void (ConfigInterpreter::*directivesHandlers[])(ConfigParserNode*)
													);

													~ConfigInterpreterContext(void);
		
		// --- Operators Overload ---
		ConfigInterpreterContext&	operator=(const ConfigInterpreterContext& rhs);

	private:
		std::vector<std::string>					context_;
		std::vector<std::string>					validBlocks_;
		std::vector<std::string>					validDirectives_;
		std::vector<void (*)(ConfigParserNode*)>	directivesHandlers_;
};


#endif