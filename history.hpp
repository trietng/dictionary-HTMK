#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

constexpr char history_output[] = "data\\history\\";
const int historyMax = 100;

class historyEntry {
public:
	string filepath;
	string word;
};

class history {
public:
	vector<string> vec;
	string historyFilePath;
	//vector<historyEntry> vec;
	~history();
	void printHistory();
	void add_word_to_history(string word);
};

history loadHistory(string filepath);