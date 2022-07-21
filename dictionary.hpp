#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "history.hpp"
#include <filesystem>
#include "ds\trie.hpp"
#include "game.hpp"
#include "favourites.hpp"

constexpr char grave_accent = '`';

enum rmode {
	text = 0, binary = 1
};

template <unsigned int N_WORD, unsigned int N_DEF>
class dictionary {
private:
	trie<N_WORD> word;
	trie<N_DEF> definition;
	std::string filepath;
	history History;
	//Very dangerous operation, proceed with caution
	void assign_key_count(trie<N_WORD>& trie) {
		/*WARNING: If N_DEF == N_WORD there will be no way to prevent a false assignment
		//at compile time (pass this->definition instead of this->word). (1)
		//
		//Since the word trie is reconstructed from raw data instead of sequential insertions,
		//it will not modify the key_count value and its key_count will stay at 0. And due to the
		//reconstruction can only be done from dictionary class instead of trie, it is obvious
		//that we will assign the key_count value of this->defintion to this->word.
		//However, member counters of classes are required to be private so that it cannot be
		//assigned value at will. Accidental assignment of values to counters can lead to
		//catastrophic scenarios (unstable randomize functions, ...). Therefore, we must
		//find another way to set the value of this->word.key_word safely.
		//
		//There are two ways to do this:
		//1. Make dictionary a derived class of trie (bad idea)
		//2. Using friend function
		//
		//friend function is the key here. It limits human error down to only one possible
		//scenario, where the developer will have to wreck things up really bad to get that
		//warned exception at (1). Even if they did do that, it is easier to find out
		//what went wrong than the public this->word.key_count solution, since
		//this->word.key_count must be 0 to get assigned.
		*/
		if (trie.count() == 0) trie.key_count = definition.count();
		// else thow std::string("INVALID ASSIGNMENT OPERATIONS");
		
		//trying not to throw things here
		//throwing exceptions aren't a good practice in C++ where there is no
		//garbage collector - aborting the program also means massive memory leak
	}
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
	//Read from text file
	void read_text(const std::string& filepath) {
		std::ifstream fin(filepath);
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
	//Read from binary file
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
	//Write to binary file
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
	//Default constructor, binary file mode
	dictionary(const std::string& filepath) {
		this->filepath = filepath;
		this->History = loadHistory(filepath);
		std::ifstream fin(filepath, std::ios::binary);
		if (fin) {
			for (unsigned int i = 0; i < N_WORD; ++i) {
				read(fin, word.top()->next[i]);
			}
			assign_key_count(this->word);
		}
		else std::cout << "ERROR: BAD FILE AT " << filepath;
	}
	//Default constructor, optional file mode
	dictionary(const std::string& filepath, rmode mode) {
		this->filepath = filepath;
		this->History = loadHistory(filepath);
		if (mode == binary) {
			std::ifstream fin(filepath, std::ios::binary);
			if (fin) {
				for (unsigned int i = 0; i < N_WORD; ++i) {
					read(fin, word.top()->next[i]);
				}
				assign_key_count(this->word);
			}
			else std::cout << "ERROR: BAD FILE AT " << filepath;
		}
		else {
			std::ifstream fin(filepath);
			if (fin) {
				std::string line, word, def;
				while (getline(fin, line)) {
					std::stringstream ss(line);
					std::getline(ss, word, '`');
					std::getline(ss, def);
					insert(word, def);
				}
			}
			else std::cout << "ERROR: BAD FILE AT " << filepath;
		}
	}
	//Copy constructor
	dictionary(const dictionary<N_WORD, N_DEF>& _source) {
		word = _source.word;
		definition = _source.definition;
		filepath = _source.filepath;
		History = _source.History; //!!!!
	}
	//Copy assignment
	dictionary<N_WORD, N_DEF>& operator=(const dictionary<N_WORD, N_DEF>& _source) {
		if (this != &_source) {
			word = _source.word;
			definition = _source.definition;
			filepath = _source.filepath;
			History = _source.History; //!!!!
		}
		return *this;
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
	entry* find_word(const std::string& word) {
		History.add_word_to_history(word,keyword);
		return this->word.find(word);
	}
	std::vector<entry*> find_definition(const std::string& keyword) {
		History.add_word_to_history(word, definition);
		return this->definition.find_d(keyword);
	}

	void seeHistory() {
		History.printHistory();
	}

	void seeFavourite() {

	}

	//Write to text file
	void write_text() {
		std :: ofstream fout(filepath + ".txt");
		fout.close();
		fout.open(filepath + ".txt", std::ios::app);
		if (fout) write_text(word.top(), fout);
	}

	entry* find_rand_word() {
		return word.random();
	}

	// check bug:
	void print_random_word() {
		entry* value = find_rand_word();
		std::cout << value->key << "  " << value->value << std::endl;
		return;
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
		read_text(temp);
	}
	//Act like find_word
	entry* operator[](const std::string& _keyword) {
		return find_word(_keyword);
	}
};