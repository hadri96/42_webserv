#ifndef CONFIG_INTERPRETER_HPP
# define CONFIG_INTERPRETER_HPP

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
		// --- Private Methods ---
		void 				interpret(ConfigParserNode* node, std::vector<std::string>& context);
};

#endif