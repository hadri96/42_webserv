#ifndef CONFIG_CONFIG_CGI_HPP
# define CONFIG_CONFIG_CGI_HPP

# include <string>
# include <vector>

# include "Path.hpp"

class	ConfigCgi
{
	public:
		// --- Constructors and Destructor ---
											ConfigCgi(void);
											ConfigCgi(const ConfigCgi& other);

											~ConfigCgi(void);

		// --- Operators Overload ---
		ConfigCgi&							operator=(const ConfigCgi& rhs);

		// --- Setters and Getters ---
		void								setExecutable(Path executable);
		void								setParameters(const std::string& parameters);
		void								addExtension(const std::string& extension);

		Path								getExecutable(void) const;
		std::string							getParameters(void) const;

		std::vector<std::string>			getExtensions(void) const;
		bool								hasExtension(const std::string& extension);

	private:
		// --- Private Attributes ---
		std::vector<std::string>			extensions_;
		Path								executable_;
		std::string							parameters_;
};

#endif
