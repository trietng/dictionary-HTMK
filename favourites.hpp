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
	void mark(entry* ent);
	void save();
	fav_word(); // load
	bool remove(string i);
	void display();
};

