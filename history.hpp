#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

constexpr char history_output[] = "data\\history\\";
const int historyMax = 100;

class history {
public:
	vector<string> vec;
	string historyFilePath;
	~history();
	void printHistory();
	void add_word_to_history(string word);
};

history loadHistory(string filepath);