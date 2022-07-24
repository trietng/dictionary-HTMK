#pragma once
#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include "menu.hpp"

using namespace std;

/*void test() {
	 auto start = std::chrono::high_resolution_clock::now();
	check bugs :
	for (int i = 0; i < 100; i++) {
			guess_definition_meaning(dict);
			guess_keyword_meaning(dict);
	}
		
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Load time: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	 << "ms\n";
}*/

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	dictionary dict(std::string(dictionary_path) + "slang", binary);
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Load time: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	auto k = dict.find_word("1D");
	//dict.rename("Slang Dictionary");
  	dict.write();
	return 0;
}