#ifndef FILE_HPP
# define FILE_HPP

# include "Path.hpp"

# include <string>
# include <fstream>

class	File
{
	public:
		// --- Constructors and Destructor ---
							File(void);
							File(const File& other);
							File(const std::string& filename);
							File(const Path& path);
							~File(void);

		// --- Operators Overload ---
		File&				operator=(const File& rhs);

		// --- Setters and Getters ---
		void				setContent(void);
		const std::string&	getContent(void) const;
		const std::string	getContent(Path& path) const;
		const Path&			getPath(void) const;

		std::string			read(void) const;

	private:
		// --- Private Attributes ---
		std::ifstream		file_;
		Path				path_;
		std::string			content_;
};

#endif
