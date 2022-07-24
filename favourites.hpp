#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "ds\\trie.hpp"
#include <vector>
#include <sstream>
#include <algorithm>

constexpr char favourite_output[] = "data\\favourite\\";

using namespace std;
class fav_word {
public:
	vector<entry> vec;
	string favouriteFilepath;
	void write();
	void mark(entry ent);
	void remove(entry ent);
	void display();
	void clear();
};

bool compare_entry(entry x, entry y);
fav_word loadFavourite(string filename);

