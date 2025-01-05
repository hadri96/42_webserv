#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// External libraries
# include <cstring>
# include <ctime>
# include <iostream>
# include <fstream>
# include <sstream>
# include <iomanip>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <cstdlib>
# include <map>
# include <vector>
# include <poll.h>
# include <fcntl.h>

// Our HPP files
# include "colors.hpp"
# include "defines.hpp"
# include "utils.hpp"
# include "EventLoop.hpp"
# include "ResponseHeader.hpp"
# include "ClientConnection.hpp"
# include "HTMLParser.hpp"
# include "HTTPResponse.hpp"
# include "HTTPRequest.hpp"

#endif
