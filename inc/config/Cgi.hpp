#ifndef CGI_HPP
# define CGI_HPP

# include <string>
# include <vector>

# include "Path.hpp"
# include "HttpMethodType.hpp"

class	Cgi
{
	private:
		Path						rootPath_;
		std::string					fileExtension_;
		std::vector<HttpMethodType>	allowedMethods_;
		Path						workingDirectory_;
		Path						scriptPath_;
	};

#endif