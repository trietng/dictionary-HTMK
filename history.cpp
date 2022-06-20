#include "history.hpp"

vector<string> loadHistory(){
    int n;
    string x;
    vector<string> temp;
    ifstream fin(history_output);
    if (fin){
        fin >> n;
        for (int i = 0; i < n;++i){
            fin >> x;
            temp.push_back(x);
        }
    }else 
    {
        cout << "Can't open the file!\n";
    }
    fin.close();
    return temp;
}

void saveHistory(vector<string> temp){
    ofstream fout(history_output);
    if (fout){
        cout << temp.size() << " ";
        for (int i = 0; i < temp.size(); ++i) fout << temp[i] << " ";
    }
    else cout << "Can't not open the file!";
    fout.close();
}

void printHistory(vector<string> temp){
    cout << "The history of search words is:\n ";
    for (int i = temp.size() - 1 ; i >= 0; --i){
        cout << temp[i] << endl;
    }
}

void add_word_to_history(string& word,vector<string>& temp){
    temp.push_back(word);
    if (temp.size() == 20) temp.erase(temp.begin());
}

void clearHistory(vector<string>& temp){
    temp.clear();
    saveHistory(temp);
}