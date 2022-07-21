#pragma once
#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

using namespace std;

void test() {
	 auto start = std::chrono::high_resolution_clock::now();
	/*
	check bugs :
	for (int i = 0; i < 100; i++) {
			guess_definition_meaning(dict);
			guess_keyword_meaning(dict);
	}
	*/
		
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Load time: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	 << "ms\n";
}

int main() {
	test();
	//std::system("pause");
	dictionary<ASCII, ASCII> dict("data\\raw\\test", binary);
	dict.write();
	dict.seeHistory();
	return 0;
}