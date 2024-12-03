#ifndef ROUTE_HPP
# define ROUTE_HPP

# include <vector>

# include "HttpMethodType.hpp"
# include "HttpRedirection.hpp"
# include "Uri.hpp"
# include "Cgi.hpp"

class	Route
{
	public:
	// --- Constructors and Destructor ---
										Route(void);
										Route(const Route& other);

										~Route(void);

	// --- Operators Overload ---
	Route&								operator=(const Route& rhs);

	// --- Setters and Getters ---
	void								setUri(const Uri& uri);
	void								setRootPath(const Path& rootPath);
	void								setRedirection(const HttpRedirection& redirection);
	void								setAutoIndex(bool autoIndex);
	void								setDefaultFile(const Path& defaultFile);
	void								setUploadDirectory(const Path& uploadDirectory);
	void								setIsCgi(bool isCgi);
	void								setCgi(const Cgi& cgi);
	void								addAllowedMethod(HttpMethodType method);

	const Uri&							getUri(void) const;
	const Path&							getRootPath(void) const;
	const HttpRedirection&				getRedirection(void) const;
	bool								getAutoIndex(void) const;
	const Path&							getDefaultFile(void) const;
	const Path&							getUploadDirectory(void) const;
	bool								getIsCgi(void) const;
	const Cgi&							getCgi(void) const;
	const std::vector<HttpMethodType>&	getAllowedMethods(void) const;

	private:
		// --- Private Attributes ---
		Uri								uri_;
		Path							rootPath_;

		std::vector<HttpMethodType>		allowedMethods_;

		HttpRedirection					redirection_;
		
		bool							autoIndex_;
		Path							defaultFile_;
		Path							uploadDirectory_;

		bool							isCgi_;
		Cgi								cgi_;
};

#endif
