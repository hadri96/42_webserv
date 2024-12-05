#ifndef PATH_HPP
# define PATH_HPP

# include <Logger.hpp>

# include <string>

class Config;

class	Path
{
	public:
		// --- Constructors and Destructor ---
					Path(void);
					Path(const Path& other);
					Path(const std::string path);
					~Path(void);

		// --- Operators Overload ---
		Path&		operator=(const Path& rhs);

		// --- Getters & Setters ---
		std::string	getPath() const;
		std::string	getPath(Config& config) const;

	private:
		// --- Private Attributes ---
		std::string	path_;

		// --- Private Methods ---
		bool	isInFileSystem() const;
		bool	isInConfig(Config& config) const;

};

#endif
