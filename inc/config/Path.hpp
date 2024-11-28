#ifndef PATH_HPP
# define PATH_HPP

# include <string>

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

	private:
		// --- Private Attributes ---
		std::string	path_;
};

#endif
