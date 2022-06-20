#pragma once
#include "ds\trie.hpp"

class dictionary {
private:
	trie word;
	trie definition;
public:
	void insert(const std::string& word, const std::string& definition);
	void remove(const std::string& word);
	entry* find_word(const std::string& word);
	std::vector<entry*> find_definition(const std::string& keyword);
	entry* find_rand_word();
};