#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

using namespace std;

struct entry {
	string word;
	bool type; //0: keyword, 1: definition
};

constexpr char history_output[] = "data\\history\\";
const int historyMax = 100;

class history {
public:
	vector<entry> vec;
	string historyFilePath;
	~history();
	void printHistory();
	void add_word_to_history(string word, bool type);
};

history loadHistory(string filepath);