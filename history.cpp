#pragma once
#include <cstdlib>
#include <ctime>
#include "history.hpp"

history loadHistory(string filepath) {
    history temp;
    temp.historyFilePath = history_output + filesystem::path(filepath).filename().string() + ".txt";
    ifstream fin(temp.historyFilePath);
    string ss, line,s;
    historyEntry Entry;
    while (getline(fin, line)) {
        stringstream ss(line);
        getline(ss,s, '`');
        Entry.word = s;
        getline(ss,s);
        Entry.Type = convertoType(s);
        temp.vec.push_back(Entry);
    }
    return temp;
    fin.close();
}

type convertoType(string s) {
    if (s == "0") return keyword;
    return definition;
}

history::~history() {
    ofstream fout(historyFilePath);
    if (fout) {
        for (auto i:vec) fout << i.word << "`" << i.Type << endl;
    }   
    fout.close();
}

void history::printHistory() {
    cout << "The history of search words is:\n"; 
    int x = vec.size() - 5;
    for (int i = vec.size() - 1; i >= max(x, 0); --i) {
        cout << convertTostring(vec[i].Type) << " " << vec[i].word << endl;
    }
}

string convertTostring(type temp) {
    if (temp == 0) return "keyword";
    return "definition";
}

void history::add_word_to_history(string word, type Type) {
    historyEntry Entry;
    Entry.word = word;
    Entry.Type = Type;
    vec.push_back(Entry);
    if (vec.size() > historyMax) vec.erase(vec.begin());
}

