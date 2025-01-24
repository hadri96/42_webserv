#ifndef PATH_HPP
# define PATH_HPP

# include "PathOrUri.hpp"

class	Path : public PathOrUri
{
	public:
		// --- Constructors and Destructor ---
					Path(void);
					Path(const Path& other);

					Path(const PathOrUri& other);
					Path(const std::string& str);

					~Path(void);

		// --- Operators Overload ---
		Path&		operator=(const Path& rhs);

		// --- Public Methods ---
		Path		getParent(void) const;
		Path		getAbsPath(void) const;
		bool		isInFileSystem(void) const;
		bool		isDir(void) const;
		std::string	read(void) const;

	private:
		// --- Private Methods ---
		Path		getWorkingDirectory(void) const;
};

#endif
