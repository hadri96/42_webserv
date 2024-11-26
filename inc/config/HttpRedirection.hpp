#ifndef HTTP_REDIRECTION_HPP
# define HTTP_REDIRECTION_HPP

# include "Path.hpp"

class	HttpRedirection
{
	private:
		int		statusCode_;
		Path	path;
};

#endif