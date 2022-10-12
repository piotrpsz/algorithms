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
#include "rabin-karp.hpp"
#include "bitset.h"
#include "murmur.h"
#include "bloom.h"
#include "shared.h"

using namespace std;

int main(int argc, const char * argv[]) {
	string path {getenv("HOME")};
	cout << path << endl;
	cout << shared::home_dir() << endl;

	// unsigned long x = 1000000000000;

	// cout << (8 * sizeof(unsigned )) << endl;
/*
	int const n = 4;
	auto const data = shared::random_bytes(n);
	for (auto i = 0; i < n; i++)
		cout << int(data[i]) << ", ";
	cout << endl;
*/

	/*
	BloomFilter bf{10, 0.1};
	cout << bf << endl << endl;
	bf.insert("1");
	bf.insert("2");
	bf.insert("42");

	cout << " 1: " << (bf.contains("1") ? "yes" : "no") << endl;
	cout << " 2: " << (bf.contains("2") ? "yes" : "no") << endl;
	cout << " 3: " << (bf.contains("3") ? "yes" : "no") << endl;
	cout << "42: " << (bf.contains("42") ? "yes" : "no") << endl;
	cout << "43: " << (bf.contains("43") ? "yes" : "no") << endl;
	*/

	// cout << Murmur::hash3("Hello") << endl;
	// cout << i32(Murmur::hash3("Hello", 5)) << endl;
	// cout << i32(Murmur::hash3("Hello", 20)) << endl;
	// cout << Murmur::hash3("Hello", 20) << endl;

	// Bitset bs{15};
	// bs.toggle(8);
	// cout << bs << endl;
	// cout << "is set: " << (bs.is_set(8) ? "true" : "false") << endl;
	// bs.unset(8);
	// cout << bs << endl;


	// auto idx = RabinKarp::index_of("Piotr x Pszczolkowski", "i", 2);
	// cout << idx << endl;
	// Way3 w;
	// Roman::test_integer();
	// Roman::test_roman();
	// auto r = Roman::integer("MMVI");
	// cout << r << endl;
	
	
	// std::string pathA { "/Users/piotr/test/test1.txt" };
	// std::string pathB { "/Users/piotr/test/test2.txt" };
	// auto p = Parser(pathA, pathB);
	// if (p.run())
	// 	p.print_diff();
	

	std::cout << "OK\n";
	return 0;
}
