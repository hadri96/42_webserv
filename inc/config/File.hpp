#ifndef FILE_HPP
# define FILE_HPP

# include <string>
# include <fstream>

class	File
{
	public:
		// --- Constructors and Destructor ---
							File(void);
							File(const File& other);

							File(const std::string& filename);

							~File(void);

		// --- Operators Overload ---
		File&				operator=(const File& rhs);

		// --- Setters and Getters ---
		void				setContent(void);
		const std::string&	getContent(void) const;

	private:
		// --- Private Attributes ---
		std::ifstream		file_;
		std::string			content_;
};

#endif
