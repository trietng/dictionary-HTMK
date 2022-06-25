#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

void test() {
	dictionary<ASCII, ASCII> dict("raw\\slang.txt");
	dict.printDictionary();
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	test();
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Load time: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	<< "ms\n";
	std::system("pause");
	return 0;
}