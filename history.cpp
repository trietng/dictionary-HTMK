#include "history.hpp"

history loadHistory(string filepath) {
    history temp;
    temp.historyFilePath = history_output + filesystem::path(filepath).filename().string() + ".txt";
    ifstream fin(temp.historyFilePath);
    int n; 
    fin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        fin >> s;
        temp.vec.push_back(s);
    }
    return temp;
    fin.close();
}

history::~history() {
    ofstream fout(historyFilePath);
    if (fout) {
        fout << vec.size() << endl;
        for (int i = 0; i < vec.size(); ++i) fout << vec[i] << endl;
    }   
    fout.close();
}

void history::printHistory() {
    cout << "The history of search words is:\n"; int x = vec.size() - 5;
    for (int i = vec.size() - 1; i >= max(x, 0); --i) {
        cout << vec[i] << endl;
    }
}

void history::add_word_to_history(string word) {
    vec.push_back(word);
    if (vec.size() > historyMax) vec.erase(vec.begin());
}