//
//  main.cpp
//  lcs
//
//  Created by Piotr Pszczółkowski on 04/09/2022.
//

// cmake .
// cmake --build .
// ./algo

#include <iostream>
#include <vector>
#include "parser.hpp"
#include "way3.hpp"
#include "roman.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
	// Way3 w;
	Roman::test_integer();
	Roman::test_roman();
	// auto r = Roman::integer("MMVI");
	// cout << r << endl;
	
	/*
	std::string pathA { "/Users/piotr/test/test1.txt" };
	std::string pathB { "/Users/piotr/test/test2.txt" };
	auto p = Parser(pathA, pathB);
	if (p.run())
		p.print_diff();
	*/

	// std::cout << "OK\n";
	return 0;
}
