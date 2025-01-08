#ifndef PATH_HPP
# define PATH_HPP

# include <Logger.hpp>
# include <Uri.hpp>
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
		std::string			getPath() const;
		std::string			getPath(Config& config) const;
		std::string			addUriAndGet(Uri& uri);


		// --- Public Methods ---
		const Path			addUri(const Uri& uri) const;
		bool				isInFileSystem() const;
    

	private:
		// --- Private Attributes ---
		std::string	path_;

		// bool	isInConfig(Config& config) const;

};

Path operator+(const Path& path, const Uri& uri);

#endif
