#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

void test() {
	dictionary dict;
	std::ifstream fin("raw/slang.txt");
	std::string line, word, def;
	while (getline(fin, line)) {
		std::stringstream ss(line);
		std::getline(ss, word, '`');
		std::getline(ss, def);
		dict.insert(word, def);
	}
	auto x = dict.find_word("Slag");
	dict.remove("Slag");
}

int main() {
	test();
	return 0;
}