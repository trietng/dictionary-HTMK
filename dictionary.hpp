#pragma once
#include <iostream>
#include <fstream>
#include "ds\trie.hpp"

template <unsigned int N_WORD, unsigned int N_DEF>
class dictionary {
private:
	trie<N_WORD> word;
	trie<N_DEF> definition;
	std::string filename;
	void printDictionary(tnode<N_WORD>* root, std::ofstream& fout) {
		if (!root) return;
		if (!root->value.empty()) {
			auto ent = root->value.front().get();
			fout << ent->key << "`" << ent->value << "\n";
		}
		for (unsigned int i = 0; i < N_WORD; ++i) {
			printDictionary(root->next[i], fout);
		}
	}
public:
	dictionary(std::string filename) {
		std::ifstream fin(filename);
		this->filename = filename;
		if (fin) {
			std::string line, word, def;
			while (getline(fin, line)) {
				std::stringstream ss(line);
				std::getline(ss, word, '`');
				std::getline(ss, def);
				insert(word, def);
			}
		}
	}
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

	void printDictionary() {
		std :: ofstream fout(filename);
		fout.close();
		fout.open(filename, std::ios::app);
		if (fout) printDictionary(word.top(), fout);
	}

	entry* find_rand_word() {

	}
};