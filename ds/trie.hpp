#pragma once
#include <string>
#include <vector>
#include <random>
#include "cqueue.hpp"
#include "shptr.hpp"

constexpr unsigned int ASCII = 95;
constexpr unsigned int ALPHA = 26;

class entry {
public:
	std::string key;	//keyword
	std::string value; //definition
	entry(const std::string& key, const std::string& value) {
		this->key = key;
		this->value = value;
	}
};

template <unsigned int SIZE>
class tnode {
public: // random function:
	int word_count; // count word in trie to random
public:
	char key;
	tnode* next[SIZE];
	cqueue<shptr<entry>> value;
	tnode() {
		key = '\0';
		for (unsigned int i = 0; i < SIZE; ++i) {
			next[i] = nullptr;
		}
		word_count = 0;
	}
	tnode(const char& key) {
		this->key = key;
		for (unsigned int i = 0; i < SIZE; ++i) {
			next[i] = nullptr;
		}
		word_count = 1;
	}
	~tnode() {
		for (unsigned int i = 0; i < SIZE; ++i) {
			delete next[i];
		}
	}
};

template <unsigned int N_TYPE>
class trie {
private:
	tnode<N_TYPE>* root;
	int get_ASSIGN() {
		switch (N_TYPE) {
		case ASCII:
			return 32;
			break;
		case ALPHA:
			return 65;
			break;
		default:
			break;
		}
		return INT32_MAX;
	}
	int ASSIGN = get_ASSIGN();

	int index(const char& key) {
		return (int)key - ASSIGN;
	}

	char getCharFromIndex(const int& index) {
		return '\0' + index + ASSIGN;
	}
	//Check if a node has any child
	bool is_leaf(tnode<N_TYPE>* node) {
		for (unsigned int i = 0; i < N_TYPE; ++i) {
			if (!node->next[i]) return false;
		}
		return true;
	}
	//Private recursive remove function
	tnode<N_TYPE>* remove(tnode<N_TYPE>* root, const std::string& key, const int& depth) {
		if (!root) return nullptr;
		root->word_count--;	 // in every node, if this node is created from n word, word_count is equal with n

		if (depth == key.size()) {
			if (!root->value.empty()) {
				root->value.front()->key = "";
				root->value.pop_front();
			}
			if (is_leaf(root)) {
				delete root;
				root = nullptr;
			}
			return root;
		}
		int i = index(key[depth]);
		root->next[i] = remove(root->next[i], key, depth + 1);
		if (is_leaf(root) && root->value.empty()) {
			delete root;
			root = nullptr;
		}
		return root;
	}
	//Private recursive find definition function
	void find_d(tnode<N_TYPE>* node, std::vector<entry*>& vt) {
		if (!node) return;
		if (!node->value.empty()) {
			for (auto i = node->value.cbegin(); i != nullptr; ++i) {
				if ((*i)->key != "") vt.push_back((*i).get());
			}
			return;
		}
		for (unsigned int i = 0; i < N_TYPE; ++i) {
			find_d(node->next[i], vt);
		}
	}

private: // random function:
	void at(int index, std::string& word, int depth) {
		int sum = 0;
		for (int i = 0; i < N_TYPE; i++) {
			tnode* temp = root->next[i];
			if (temp == nullptr || temp->word_count == 0)
				continue;
			
			int size = temp->word_count;
			if (index < sum + size) {
				temp->at(index - sum, word, depth + 1);
				word[depth] = getCharFromIndex(i);
				return;
			}

			sum = sum + size;
		}
	}

public: // random function:
	
	std::random_device dev;
	std::mt19937 rng;

	// return a random string
	std::string random() {
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, root->word_count - 1);
		return at(dist(rng));
	}

	// return the string at a given index
	std::string at(int index) {
		string word = "";
		at(index, word, 0);
		return word;
	}



public:
	trie() {
		root = new tnode<N_TYPE>();
		word_count = 0;
	}
	~trie() {
		delete root;
	}
	//Return the root node
	tnode<N_TYPE>*& top() {
		return root;
	}
	void clear() {
		delete root;
		root = new tnode<N_TYPE>();
	}
	//Insert entry into the word trie
	void insert(const shptr<entry>& entry) {
		tnode<N_TYPE>* cur = root;
		for (const auto& i : entry->key) {
			int j = index(i);
			if (!cur->next[j]) cur->next[j] = new tnode<N_TYPE>(i);
			cur = cur->next[j];
			cur->word_count++; // in every node, if this node is created from n word, word_count is equal with n
		}
		cur->value.push_back(entry);
		
	}
	//Insert entry into the definition trie
	void insert_d(const shptr<entry>& entry) {
		tnode<N_TYPE>* cur = root;
		for (const auto& i : entry->value) {
			int j = index(i);
			if (!cur->next[j]) cur->next[j] = new tnode<N_TYPE>(i);
			cur = cur->next[j];
			cur->word_count++; // in every node, if this node is created from n word, word_count is equal with n

		}
		cur->value.push_back(entry);
		
	}
	//Remove keyword from the keyword trie
	void remove(const std::string& key) {
		remove(this->root, key, 0);
	}
	//Find keyword inside the keyword trie
	entry* find(const std::string& key) {
		tnode<N_TYPE>* cur = root;
		for (const auto& i : key) {
			int j = index(i);
			if (!cur->next[j]) return nullptr;
			cur = cur->next[j];
		}
		return cur->value.front().get();
	}
	//Find definition insert the definition trie
	std::vector<entry*> find_d(const std::string& def) {
		std::vector<entry*> vt;
		tnode<N_TYPE>* cur = root;
		for (const auto& i : def) {
			int j = index(i);
			if (!cur->next[j]) return vt;
			cur = cur->next[j];
		}
		find_d(cur, vt);
		return vt;
	}
};