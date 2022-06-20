#pragma once
#include <fstream>
#include <string>
#include <vector>

constexpr char history_output[] = "data\\history.txt";

using namespace std;

vector<string> load_history();

void write_history(const vector<string>& history, const string& word);

void clear_history(vector<string>& history);