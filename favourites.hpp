#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "ds\\trie.hpp"
#include <vector>
#include <algorithm>

constexpr char favourite_output[] = "data\\favourites.txt";

using namespace std;
class fav_word {
private:
	vector<string> vec; //save
public:
	fav_word();
	~fav_word();
	void mark(entry* ent);
	void remove(string s);
	void display();
};

