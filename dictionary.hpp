#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "ds\trie.hpp"
constexpr char grave_accent = '`';

template <unsigned int N_WORD, unsigned int N_DEF>
class dictionary {
private:
	trie<N_WORD> word;
	trie<N_DEF> definition;
	std::string filepath;
	//Write to text file
	void write_text(tnode<N_WORD>* root, std::ofstream& fout) {
		if (!root) return;
		if (!root->value.empty()) {
			auto ent = root->value.front().get();
			fout << ent->key << "`" << ent->value << "\n";
		}
		for (unsigned int i = 0; i < N_WORD; ++i) {
			write_text(root->next[i], fout);
		}
	}
	//Read trie from binary file
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
	//Write trie to binary file
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
	dictionary(const std::string& filepath) {
		this->filepath = filepath;
		std::ifstream fin(filepath, std::ios::binary);
		if (fin) {
			for (unsigned int i = 0; i < N_WORD; ++i) {
				read(fin, word.top()->next[i]);
			}
		}
		else std::cout << "ERROR: BAD FILE AT " << filepath;
	}
	//Read from text file
	void read_text(const std::string& filepath) {
		clear();
		std::ifstream fin(filepath);
		this->filepath = filepath;
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
	//Write trie to binary file
	void write() {
		std::ofstream fout(filepath, std::ios::binary);
		if (fout) {
			for (unsigned int i = 0; i < N_WORD; ++i) {
				write(fout, word.top()->next[i]);
			}
		}
		else std::cout << "ERROR: BAD FILE AT " << filepath;
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
	//Write to text file
	void write_text() {
		std :: ofstream fout(filepath + ".txt");
		fout.close();
		fout.open(filepath + ".txt", std::ios::app);
		if (fout) write_text(word.top(), fout);
	}

	entry* find_rand_word() {

	}

	void clear() {
		word.clear();
		definition.clear();
		filepath.clear();
	}

	void restore() {
		std::string t_filepath = filepath;
		clear();
		std::string temp = "data\\backup\\" + std::filesystem::path(t_filepath).filename().string(); // ???
		dictionary(temp);
	}
};