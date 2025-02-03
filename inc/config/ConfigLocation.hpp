#ifndef CONFIG_LOCATION_HPP
# define CONFIG_LOCATION_HPP

# include <ostream>
# include <vector>

# include "Uri.hpp"
# include "HttpMethodType.hpp"
# include "ConfigRedirection.hpp"
# include "ConfigCgi.hpp"

class	ConfigLocation
{
	public:
	// --- Constructors and Destructor ---
										ConfigLocation(void);
										ConfigLocation(const ConfigLocation& other);

										~ConfigLocation(void);

	// --- Operators Overload ---
	ConfigLocation&						operator=(const ConfigLocation& rhs);
	bool								operator==(const Uri& uri) const;

	// --- Setters and Getters ---
	void								setUri(Uri uri);
	void								setRootPath(Path rootPath);
	void								setAutoIndex(bool autoIndex);

	void								setConfigRedirection(ConfigRedirection redirection);
	const ConfigRedirection&			getConfigRedirection(void) const;

	void								setDefaultFile(const Path& defaultFile);
	void								setUploadDirectory(const Path& uploadDirectory);
	void								setIsCgi(bool isCgi);
	void								setCgi(const ConfigCgi& cgi);
	void								addAllowedMethod(HttpMethodType method);

	const Uri&							getUri(void) const;
	const Path&							getRootPath(void) const;
	
	const std::string					getRootPathString(void) const;
	bool								getAutoIndex(void) const;
	const Path&							getDefaultFile(void) const;
	const Path&							getUploadDirectory(void) const;
	bool								getIsCgi(void) const;
	const ConfigCgi&					getCgi(void) const;
	const std::vector<HttpMethodType>&	getAllowedMethods(void) const;

	void								setClientMaxBodySize(int clientMaxBodySize);
	int									getClientMaxBodySize(void) const;

	void								log(void);

	bool								isMethodAllowed(HttpMethodType method) const;
	bool								isSizeAllowed(int byteSize) const;

	private:
		// --- Private Attributes ---
		Uri								uri_; // = uriSegment_;
		Path							rootPath_; 

		std::vector<HttpMethodType>		allowedMethods_;

		ConfigRedirection				redirection_; // priorite 1
		
		bool							autoIndex_; // priorite 3
		Path							defaultFile_; // priorite 2
		Path							uploadDirectory_;

		int								clientMaxBodySize_;

		bool							isCgi_;
		ConfigCgi						cgi_;
};

//std::ostream&							operator<<(std::ostream&, Location& object);

#endif
