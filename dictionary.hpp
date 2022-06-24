#pragma once
#include "ds\trie.hpp"

template <unsigned int N_WORD, unsigned int N_DEF>
class dictionary {
private:
	trie<N_WORD> word;
	trie<N_DEF> definition;
public:
	void insert(const std::string& word, const std::string& definition) {
		shptr<entry> ent(new entry(word, definition));
		this->word.insert(ent);
		this->definition.insert_d(ent);
	}
	void remove(const std::string& word) {
		this->word.remove(word);
	}
	entry* find_word(const std::string& word) {
		return this->word.find(word);
	}
	std::vector<entry*> find_definition(const std::string& keyword) {
		return this->definition.find_d(keyword);
	}
	entry* find_rand_word() {

	}
};