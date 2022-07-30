#pragma once
#include <cstdlib>
#include <ctime>
#include "history.hpp"

history loadHistory(string filename) {
    history temp;
    temp.historyFilePath = history_output + filename + ".txt";
    ifstream fin(temp.historyFilePath);
    if (fin) {
        string ss, line, s;
        historyEntry Entry;
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, s, '`');
            Entry.word = s;
            getline(ss, s);
            Entry.Type = convertoType(s);
            temp.vec.push_back(Entry);
        }
    }
    fin.close();
    return temp;
}

type convertoType(string s) {
    if (s == "0") return keyword;
    return def;
}

void history::write() {
    ofstream fout(historyFilePath);
    if (fout) {
        for (auto i:vec) fout << i.word << "`" << i.Type << endl;
    }   
    fout.close();
}

void history::printHistory() {
    if (vec.empty()) cout << "You haven't searched any word!";
    else {
        cout << "The history of search words is:\n";
        int x = vec.size() - 5;
        for (int i = vec.size() - 1; i >= max(x, 0); --i) {
            cout << convertTostring(vec[i].Type) << " " << vec[i].word << endl;
        }
    }
}

string convertTostring(type temp) {
    if (temp == 0) return "keyword";
    return "def";
}

void history::add_word_to_history(string word, type Type) {
    historyEntry Entry;
    Entry.word = word;
    Entry.Type = Type;
    vec.push_back(Entry);
    if (vec.size() > historyMax) vec.erase(vec.begin());
}

void history::clear() {
    vec.clear();
    historyFilePath.clear();
}

