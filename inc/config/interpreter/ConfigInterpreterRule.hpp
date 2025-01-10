#ifndef CONFIG_INTERPRETER_RULE_HPP
# define CONFIG_INTERPRETER_RULE_HPP

# include "ConfigParserNode.hpp"

# include <vector>
# include <string>

class	ConfigInterpreterRule
{
	public:
		// --- Constructors and Destructor ---
													ConfigInterpreterRule(void);
													ConfigInterpreterRule(const ConfigInterpreterRule& other);

													ConfigInterpreterRule(
														const char* context[], 
														const char* validBlocks[],
														const char* validDirectives[]
													);

													~ConfigInterpreterRule(void);
		
		// --- Operators Overload ---
		ConfigInterpreterRule&	operator=(const ConfigInterpreterRule& rhs);

		// --- Setters and Getters ---
		const std::vector<std::string>&				getContext(void) const;
		const std::vector<std::string>&				getValidBlocks(void) const;
		const std::vector<std::string>&				getValidDirectives(void) const;

		// --- Public Methods ---
		bool										isValidBlock(std::string block) const;
		bool										isValidDirective(std::string directive) const;

	private:
		std::vector<std::string>					context_;
		std::vector<std::string>					validBlocks_;
		std::vector<std::string>					validDirectives_;
		std::vector<void (*)(ConfigParserNode*)>	directivesHandlers_;
};

std::ostream&	operator<<(std::ostream& os, const ConfigInterpreterRule& object);


#endif