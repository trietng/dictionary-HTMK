#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>

constexpr char history_output[] = "data\\history.txt";

using namespace std;

vector<string> loadHistory();

void saveHistory(vector<string> temp);

void printHistory(vector<string> temp);

void add_word_to_history(string& word,vector<string>& temp);

void clearHistory(vector<string>& temp);