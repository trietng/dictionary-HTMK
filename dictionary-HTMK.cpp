#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

void test() {
	dictionary<ASCII, ASCII> dict;
	std::ifstream fin("raw/slang.txt");
	std::string line, word, def;
	while (getline(fin, line)) {
		std::stringstream ss(line);
		std::getline(ss, word, '`');
		std::getline(ss, def);
		dict.insert(word, def);
	}
	auto start = std::chrono::high_resolution_clock::now();
	auto x = dict.find_definition("Radio");
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Searching time: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	<< "ms\n";
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