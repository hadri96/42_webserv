#ifndef CGI_HPP
# define CGI_HPP

# include <string>
# include <vector>

# include "Path.hpp"
# include "HttpMethodType.hpp"

class	Cgi
{
	public:
		// --- Constructors and Destructor ---
											Cgi(void);
											Cgi(const Cgi& other);

											~Cgi(void);

		// --- Operators Overload ---
		Cgi&								operator=(const Cgi& rhs);

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
