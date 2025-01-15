#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <ostream>
# include <vector>

# include "HttpMethodType.hpp"
# include "HttpRedirection.hpp"
# include "Uri.hpp"
# include "Cgi.hpp"

class	Location
{
	public:
	// --- Constructors and Destructor ---
										Location(void);
										Location(const Location& other);

										~Location(void);

	// --- Operators Overload ---
	Location&								operator=(const Location& rhs);

	// --- Setters and Getters ---
	void								setUri(Uri uri);
	void								setRootPath(Path rootPath);
	void								setAutoIndex(bool autoIndex);

	void								setHttpRedirection(HttpRedirection redirection);
	const HttpRedirection&				getHttpRedirection(void) const;

	void								setDefaultFile(const Path& defaultFile);
	void								setUploadDirectory(const Path& uploadDirectory);
	void								setIsCgi(bool isCgi);
	void								setCgi(const Cgi& cgi);
	void								addAllowedMethod(HttpMethodType method);

	const Uri&							getUri(void) const;
	const Path&							getRootPath(void) const;
	const std::string					getRootPathString(void) const;
	bool								getAutoIndex(void) const;
	const Path&							getDefaultFile(void) const;
	const Path&							getUploadDirectory(void) const;
	bool								getIsCgi(void) const;
	const Cgi&							getCgi(void) const;
	const std::vector<HttpMethodType>&	getAllowedMethods(void) const;

	void								log(void);

	private:
		// --- Private Attributes ---
		Uri								uri_; // = uriSegment_;
		Path							rootPath_; 

		std::vector<HttpMethodType>		allowedMethods_;

		HttpRedirection					redirection_; // priorite 1
		
		bool							autoIndex_; // priorite 3
		Path							defaultFile_; // priorite 2
		Path							uploadDirectory_;

		bool							isCgi_;
		Cgi								cgi_;
};

//std::ostream&							operator<<(std::ostream&, Location& object);

#endif
