#pragma once
#include <cstdlib>
#include <ctime>
#include "header.hpp"
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
            getline(ss, s,'`');
            Entry.Type = convertoType(s);
            getline(ss, s);
            Entry.time = s;
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
        for (auto i:vec) fout << i.word << "`" << i.Type << "`" << i.time << endl;
    }   
    fout.close();
}

void history::printHistory() {
    if (vec.empty()) cout << "You haven't searched any word!";
    else {
        SetColor(4);
        cout << left << setw(3) << " " <<left << setw(20) << "Keyword" << left << setw(20) << "Type" << left << setw(20) << "time" << endl;
        for (int i = vec.size() - 1; i >= 0; --i) {
            SetColor(15);
            cout << left << setw(15) << vec[i].word << left << setw(20) << convertTostring(vec[i].Type) << left << setw(20) << vec[i].time << endl;
        }
    }

    cout << "\nPress any key to continue..." << endl;
    _getch();
}

string convertTostring(type temp) {
    if (temp == 0) return "Search for keyword";
    return "Search for definition";
}

void history::add_word_to_history(string word, type Type,string time) {
    historyEntry Entry;
    Entry.word = word;
    Entry.Type = Type;
    Entry.time = time;
    vec.push_back(Entry);
    if (vec.size() > historyMax) vec.erase(vec.begin());
}

void history::clear() {
    vec.clear();
    historyFilePath.clear();
}

