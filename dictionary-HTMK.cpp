#pragma once
#include "dictionary.hpp"
//#include "restore.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

void test() {
	dictionary<ASCII, ASCII> dict("data\\raw\\slang.txt");
	dict.write();
	/*
	restore<ASCII, ASCII> res(dict, "data\\tempDel\\slang.txt");
	res.reloadWordTree();
	*/
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	dictionary<ASCII, ASCII> dict("data\\raw\\test", binary);
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "Load time: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	<< "ms\n";
	std::system("pause");
	dict.write();
	return 0;
}