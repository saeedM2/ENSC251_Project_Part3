//============================================================================
// Name        : dirTree.cpp
// Description : Course Project Part 3 (Directory Tree main program)
// Copyright (c) 2016 - Craig Scratchley - wcs (at) sfu (dot) ca
//============================================================================

#include "makeDirectoryTree.hpp"

using namespace std;

int doStuff()
{
	// call function to build directory tree in memory
	auto root_dir1P = make_directory_tree(".", "test_dir");

	if (root_dir1P) {
		root_dir1P->print_traverse(nullptr);
		OUT << endl;

		root_dir1P->reset_count();
		root_dir1P->count_traverse(nullptr);
		OUT << "Count is " << root_dir1P->get_count() << "\n" << endl;

		auto root_dir2 = Directory(*root_dir1P); // copy construction
		root_dir2.print_traverse(nullptr);
		OUT << endl;

		auto root_dir3P = make_directory_tree("test_dir", "Lectures");
		if (root_dir3P) {
			root_dir2 = *root_dir3P; // overloaded copy assignment operation
			OUT << endl;

			delete root_dir3P;
			OUT << endl;
		}
		root_dir2.print_traverse(nullptr);
		OUT << endl;

		delete root_dir1P;
		OUT << endl;

	} // destructor for root_dir2 called.
	OUT << endl;

	return 0;
}

// don't remove the below line.
#ifndef DONT_RUN_MAIN
int main()
{
	int rv = doStuff();

#ifdef USE_OSS
	std::string s = oss.str();
	cout << s << endl;
#endif

	return rv;
}
#endif

/* End of dirTree.cpp file */
