#pragma once
#include <iostream>
#include <fstream>
#include "ds\trie.hpp"
constexpr char grave_accent = '`';

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
	//Read trie from file
	void read(std::ifstream& fin, tnode<N_WORD>*& node) {
		char ch = '\0';
		fin.read((char*)&(ch), sizeof(char));
		if (ch == '`') node = nullptr;
		else {
			node = new tnode<N_WORD>(ch);
			int len = 0;
			fin.read((char*)&len, sizeof(int));
			if (len > 0) {
				char* buf_word = new char[len];
				fin.read(buf_word, len);
				std::string word(buf_word);
				delete[] buf_word;
				fin.read((char*)&len, sizeof(int));
				char* buf_def = new char[len];
				fin.read(buf_def, len);
				std::string def(buf_def);
				delete[] buf_def;
				shptr<entry> ent(new entry(word, def));
				node->value.push_back(ent);
				this->definition.insert_d(ent);
			}
			for (unsigned int i = 0; i < N_WORD; ++i) {
				read(fin, node->next[i]);
			}
		}
	}
	//Write trie to file
	void write(std::ofstream& fout, tnode<N_WORD>* node) {
		if (!node) fout.write((char*)&(grave_accent), sizeof(char));
		else {
			fout.write((char*)&(node->key), sizeof(char));
			int len = 0;
			if (node->value.empty()) fout.write((char*)&len, sizeof(int));
			else {
				//Write word
				len = node->value.front()->key.size() + 1;
				fout.write((char*)&len, sizeof(int));
				fout.write(node->value.front()->key.c_str(), len);
				//Write definition
				len = node->value.front()->value.size() + 1;
				fout.write((char*)&len, sizeof(int));
				fout.write(node->value.front()->value.c_str(), len);
			}
			for (unsigned int i = 0; i < N_WORD; ++i) {
				write(fout, node->next[i]);
			}
		}
	}
public:
	dictionary(const std::string& filename) {
		this->filename = filename;
		std::ifstream fin(filename, std::ios::binary);
		if (fin) {
			for (unsigned int i = 0; i < N_WORD; ++i) {
				read(fin, word.top()->next[i]);
			}
		}
		else std::cout << "ERROR: BAD FILE AT " << filename;
	}
	//Write trie to file
	void write() {
		std::ofstream fout(filename, std::ios::binary);
		if (fout) {
			for (unsigned int i = 0; i < N_WORD; ++i) {
				write(fout, word.top()->next[i]);
			}
		}
		else std::cout << "ERROR: BAD FILE AT " << filename;
	}
	void insert(const std::string& word, const std::string& definition) {
		shptr<entry> ent(new entry(word, definition));
		this->word.insert(ent);
		this->definition.insert_d(ent);
	}
	void remove(const std::string& word) {
		this->word.remove(word);
	}
	// Add Remove Definition trie:

	void remove_def(const std::string& def) {
		this->definition.remove(def);
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