#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "ds\\trie.hpp"
#include <vector>
#include <sstream>
#include <algorithm>

constexpr char favourite_output[] = "data\\favourites.txt";

using namespace std;
class fav_word {
private:
	vector<entry> vec; //save
public:
	fav_word();
	~fav_word();
	void mark(entry ent);
	void remove(entry ent);
	void display();
};

bool compare_entry(entry x, entry y);

