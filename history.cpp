#pragma once
#include <cstdlib>
#include <ctime>
#include "history.hpp"

history loadHistory(string filepath) {
    history temp;
    temp.historyFilePath = history_output + filesystem::path(filepath).filename().string() + ".txt";
    ifstream fin(temp.historyFilePath);
    int n; 
    string ss, line;
    entry Entry;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        getline(fin, line);
        stringstream ss(line);
        getline(ss, Entry.word, " ");
        getline(ss, Entry.type);
        temp.vec.push_back(Entry);
    }
    return temp;
    fin.close();
}

history::~history() {
    ofstream fout(historyFilePath);
    if (fout) {
        fout << vec.size() << endl;
        for (auto i:vec) fout << i.word << " " << i.type <<  endl;
    }   
    fout.close();
}

void history::printHistory() {
    cout << "The history of search words is:\n"; 
    int x = vec.size() - 5;
    for (int i = vec.size() - 1; i >= max(x, 0); --i) {
        cout << (vec[i].type) ? "Definition" : "Keyword"  << vec[i] << endl;
    }
}

void history::add_word_to_history(string word, bool type) {
    entry Entry;
    Entry.word = word;
    Entry.type = type;
    vec.push_back(Entry);
    if (vec.size() > historyMax) vec.erase(vec.begin());
}