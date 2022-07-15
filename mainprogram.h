#pragma once
#include "dictionary.hpp"

using namespace std;

class MainProgram {
private:
    vector<dictionary<ASCII, ASCII>> database;
    //history
    //favourite
public:
    MainProgram();
    ~MainProgram();
    vector<entry*> search_result; //to store search result
    void search_word(const std::string& input);
    void search_definition(const std::string& input);
};
