/*
 * makeDirectoryTree.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: wcs
 */

#include <dirent.h>
#include <sys/stat.h>
#include <algorithm> // for find

#include "makeDirectoryTree.hpp"

// The below function may be replaced.  Don't worry about trying to understand
//	this version.

// traverse directories on the filesystem starting at a certain point and build
//	a directory tree in memory

Directory *make_directory_tree(const std::string& path, const std::string& dir_name)
{
	using namespace std;

	static vector<string> ignore_list = {".",".."};

	auto newPath = path + "\\" + dir_name;

	DIR *dir;
	if ((dir = opendir(newPath.c_str())) == nullptr)
	{
	    OUT << newPath.c_str() << " Error while opening " << newPath << endl;
	    return nullptr;
	}
	auto new_entity = new Directory(dir_name);

	struct dirent *dptr;
	while ((dptr = readdir(dir)))
	{
		if(find(ignore_list.begin(), ignore_list.end(), dptr->d_name) != ignore_list.end())
				continue;

		auto fullPath = newPath + "\\" + dptr->d_name;

		struct stat filestat;
		stat(fullPath.c_str(), &filestat);

		if(S_ISDIR(filestat.st_mode))
		{
			auto node = make_directory_tree(newPath, dptr->d_name);
			if (!node)
				// add directory with no files or subdirs in case of permission problem
				node = new Directory(dptr->d_name);
			new_entity->add_childP(node);
		}
		else {
			new_entity->add_file(dptr->d_name);
		}
	}
	return new_entity;
}
