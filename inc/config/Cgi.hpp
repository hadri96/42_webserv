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
		Cgi&						operator=(const Cgi& rhs);

	private:
		// --- Private Attributes ---
		Path						rootPath_;
		std::string					fileExtension_;
		std::vector<HttpMethodType>	allowedMethods_;
		Path						workingDirectory_;
		Path						scriptPath_;
	};

#endif
