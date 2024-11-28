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
		std::string					fileExtension_;
		Path						rootPath_;
		std::vector<HttpMethodType>	allowedMethods_;
		Path						scriptPath_;
		Path						workingDirectory_;
	};

#endif
