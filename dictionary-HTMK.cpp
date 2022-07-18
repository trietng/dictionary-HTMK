#pragma once
#include "dictionary.hpp"
//#include "restore.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
//#include <thread>

void test() {
	//auto start = std::chrono::high_resolution_clock::now();
	dictionary<ASCII, ASCII> dict("data\\raw\\test", binary);
	guess_definition_meaning(dict);
	auto copy_d = dict;
	//auto stop = std::chrono::high_resolution_clock::now();
	//std::cout << "Load time: " <<
	//std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	//<< "ms\n";
	auto x = copy_d.find_word("2M");

	
}

int main() {
	test();
	//std::system("pause");
	//dict.write();
	//dict.seeHistory();
	return 0;
}