#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

using namespace std;

enum type {
	keyword = 0,
	definition = 1
};

struct historyEntry {
	string word;
	type Type;
};

constexpr char history_output[] = "data\\history\\";
const int historyMax = 100;

class history {
public:
	vector<historyEntry> vec;
	string historyFilePath;
	~history();
	void printHistory();
	void add_word_to_history(string word, type Type);
};

history loadHistory(string filepath);
type convertoType(string s);
string convertTostring(type temp);