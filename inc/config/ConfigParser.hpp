#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

class	ConfigParser
{
	public:
		// --- Constructors and Destructor ---
						ConfigParser(void);
						ConfigParser(const ConfigParser& other);

						~ConfigParser(void);

		// --- Operators Overload ---
		ConfigParser&	operator=(const ConfigParser& rhs);
};

#endif
