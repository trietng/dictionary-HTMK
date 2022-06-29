#pragma once

#include "dictionary.hpp"

template <unsigned int N_WORD, unsigned int N_DEF>
class restore{
private:
	std::string filename;
	dictionary<N_WORD, N_DEF> dict;
	//load temptation of Trie before deleting. 
	void saveWordTrieTemp(tnode<N_WORD>* root, std::ofstream& fout) {
		if (root == nullptr)
			return;
		if (!root->value.empty()) {
			auto ent = root->value.front().get();
			fout << ent->key << "`" << ent->value << "\n";
		}
		for (unsigned int i = 0; i < N_WORD; ++i) {
			printDictionary(root->next[i], fout);
		}
	};

	void changeFilename(std::string& filename) {
		std::string temp;
		std::stringstream ss(filename);
		std::ignore(ss, "\\");
		std::ignore(ss, "\\");
		std::getline(ss, temp, "\\");
		filename = "data\\backup\\" + temp;
		return;
	}

public:
	restore(dictionary<N_WORD, N_DEF>& dict, std::string filename) {
		this->dict = dict;
		this->filename = filename;
	}


	void removeWordTrie() {
		std::ofstream fout(filename);
		fout.close();
		fout.open(filename, std::ios::app);
		void saveWordTrieTemp(dict.word.top(), fout);
		fout.close();
		std::ifstream fin(filename);
		fin.close();
		fin.open(filename, std::ios::app);
		if (fin) {
			std::string line, word, def;
			while (getline(fin, line)) {
				std::stringstream ss(line);
				std::getline(ss, word, '`');
				std::getline(ss, def);
				dict.remove(word);
				dict.remove_def(def);
			}
		}
	}

	dictionary<N_WORD, N_DEF> reloadWordTree() {
		changeFilename(filename);
		std::ifstream fin(filename);
		if (fin) {
			std::string line, word, def;
			while (getline(fin, line)) {
				std::stringstream ss(line);
				std::getline(ss, word, '`');
				std::getline(ss, def);
				this->dict.insert(word, def);
			}
		}
		return this->dict;
	}
};

