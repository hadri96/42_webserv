#include "PathOrUri.hpp"
#include "Path.hpp"
#include "Uri.hpp"

#include <iostream>

// c++ src/test/testPathOrUri.cpp src/type/PathOrUri.cpp src/type/Path.cpp src/type/Uri.cpp -I inc/type

int	main(void)
{
	Path path1("a/cool/path");
	std::cout << "path1 : " << path1 << std::endl;
	std::cout << "parent of path1 : " << path1.getParent() << std::endl;
	std::cout << "parent of parent of path1 : " << path1.getParent().getParent() << std::endl;
	std::cout << "parent of parent of parent of path1 : " << path1.getParent().getParent().getParent() << std::endl;
	std::cout << "parent of parent of parent of parent of path1 : " << path1.getParent().getParent().getParent().getParent() << std::endl;

	Path path2("i/am");
	std::cout << "path2 : " << path2 << std::endl;

	std::cout << "path2/path1 :" << path2 / path1 << std::endl;

	Path path3("dude");
	std::cout << "path3 : " << path3 << std::endl;

	std::cout << "path2/path1/path3 :" << path2 / path1 / path3 << std::endl;

	return (0);
}