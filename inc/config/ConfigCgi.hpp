#ifndef CONFIG_ConfigCgi_HPP
# define CONFIG_ConfigCgi_HPP

# include <string>
# include <vector>

# include "Path.hpp"
# include "HttpMethodType.hpp"

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
		void								setFileExtension(const std::string& fileExtension);
		void								setRootPath(const Path& rootPath);
		void								setScriptPath(const Path& scriptPath);
		void								setWorkingDirectory(const Path& workingDirectory);
		void								addAllowedMethod(HttpMethodType allowedMethod);

		const std::string&					getFileExtension(void) const;
		const Path&							getRootPath(void) const;
		const Path&							getScriptPath(void) const;
		const Path&							getWorkingDirectory(void) const;
		const std::vector<HttpMethodType>&	getAllowedMethods(void) const;

	private:
		// --- Private Attributes ---
		std::string							fileExtension_;
		Path								rootPath_;
		std::vector<HttpMethodType>			allowedMethods_;
		Path								scriptPath_;
		Path								workingDirectory_;
};

#endif
