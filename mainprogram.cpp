#include "mainprogram.h"

MainProgram::MainProgram() {
    //temporary only
    database.push_back(dictionary<ASCII, ASCII>("../data/raw/test"));
}

MainProgram::~MainProgram() {

}

void MainProgram::search_word(const std::string& input) {
    search_result.clear();
    for (auto& dict : database) {
        entry* temp = dict.find_word(input);
        if (temp) search_result.push_back(temp);
    }
}

void MainProgram::search_definition(const std::string& input) {
    search_result.clear();
    for (auto& dict : database) {
        vector<entry*> temp = dict.find_definition(input);
        search_result.reserve(search_result.size() + temp.size());
        search_result.insert(search_result.end(), temp.begin(), temp.end());
    }
}
