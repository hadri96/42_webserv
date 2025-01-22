#include "PathOrUri.hpp"
#include "Path.hpp"
#include "Uri.hpp"

#include <iostream>

// c++ src/test/testPathOrUri.cpp src/type/PathOrUri.cpp src/type/Path.cpp src/type/Uri.cpp -I inc/type

int	main(void)
{
	std::cout << "--- Test 1 : parent path ---" << std::endl;
	Path path1("a/cool/path");
	std::cout << "path1 : " << path1 << std::endl;
	std::cout << path1.getParent() << std::endl;
	std::cout << path1.getParent().getParent() << std::endl;
	std::cout << path1.getParent().getParent().getParent() << std::endl;
	std::cout << path1.getParent().getParent().getParent().getParent() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 2 : concatenation of two paths ---" << std::endl;
	Path path2("i/am");
	std::cout << "path2 : " << path2 << std::endl;
	std::cout << "path2/path1 :" << path2/path1 << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 3 : concatenation of three paths ---" << std::endl;
	Path path3("dude");
	std::cout << "path3 : " << path3 << std::endl;
	std::cout << "path2/path1/path3 :" << path2/path1/path3 << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 4 : concatenation of a path and a string (with too many '/') ---" << std::endl;
	Path path4("this/is/another");
	std::cout << "path4 : " << path4 << std::endl;
	std::cout << "path4 + string : " << path4/"path//////to/////try////out//////" << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 5 : absolute path ---" << std::endl;
	std::cout << path1.getAbsPath() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 6 : parent of an absolute path ---" << std::endl;
	std::cout << path1.getAbsPath().getParent() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 7 : is in file system ---" << std::endl;
	Path path5 = path1.getAbsPath().getParent();
	std::cout << path5 << " : " << path5.isInFileSystem() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 8 : is in file system ---" << std::endl;
	Path path6("/usr/bin");
	std::cout << path6 << " : " << path6.isInFileSystem() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 9 : is parent in file system ---" << std::endl;
	std::cout << path6.getParent() << " : " << path6.getParent().isInFileSystem() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 10 : is directory ---" << std::endl;
	std::cout << path6 << " : " << path6.isDir() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 11 : uri ---" << std::endl;
	Uri uri1("this/is/mickey/mouse");
	std::cout << "uri1 : " << uri1 << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 12 : parent of an uri ---" << std::endl;
	std::cout << uri1.getParent() << std::endl;
	std::cout << uri1.getParent().getParent() << std::endl;
	std::cout << uri1.getParent().getParent().getParent() << std::endl;
	std::cout << uri1.getParent().getParent().getParent().getParent() << std::endl;
	std::cout << uri1.getParent().getParent().getParent().getParent().getParent() << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 13 : concatenation of two uris ---" << std::endl;
	Uri uri2("/and/donald/duck/");
	std::cout << "uri2 : " << uri2 << std::endl;
	std::cout << "uri1/uri2 : " << uri1/uri2 << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 14 : concatenation of a path and an uri ---" << std::endl;
	Path path7("www/images/");
	Uri uri3("holiday/seashore1.jpg");

	std::cout << "path7 : " << path7 << std::endl;
	std::cout << "uri3 : " << uri3 << std::endl;
	std::cout << "path7/uri3 : " << path7.getAbsPath()/uri3 << std::endl;
	std::cout << std::endl;

	std::cout << "--- Test 15 : concatenation of an uri and a string ---" << std::endl;
	std::cout << Uri("mickey")/"is/a///great///guy" << std::endl;

	return (0);
}