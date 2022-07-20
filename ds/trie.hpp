#pragma once
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "cqueue.hpp"
#include "shptr.hpp"

static constexpr unsigned int ASCII = 95;
static constexpr unsigned int ALPHA = 26;
static std::random_device rd;
static std::mt19937 rng{rd()};

template <unsigned int N_WORD, unsigned int N_DEF>
class dictionary;

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
public:
	char key;
	tnode* next[SIZE];
	cqueue<shptr<entry>> value;
	tnode() {
		key = '\0';
		for (unsigned int i = 0; i < SIZE; ++i) {
			next[i] = nullptr;
		}
	}
	tnode(const char& key) {
		this->key = key;

		for (unsigned int i = 0; i < SIZE; ++i) {
			next[i] = nullptr;
		}
	}
	~tnode() {
		for (unsigned int i = 0; i < SIZE; ++i) {
			delete next[i];
		}
	}
};

template <unsigned int N_TYPE>
constexpr unsigned int ASSIGN;

template <>
constexpr unsigned int ASSIGN<ASCII> = 32;

template <>
constexpr unsigned int ASSIGN<ALPHA> = 65;

template <unsigned int N_TYPE>
class trie {
private:
	tnode<N_TYPE>* root;
	int index(const char& key) {
		return (int)key - ASSIGN<N_TYPE>;
	}
	// convert from index to char:
	char getCharFromIndex(const int& index) {
		return (char)('\0' + index + ASSIGN<N_TYPE>);
	}
	unsigned int key_count; // count word in trie to random
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
	template <unsigned int N_WORD, unsigned int N_DEF>
	friend void dictionary<N_WORD, N_DEF>::assign_key_count(trie<N_WORD>& trie);
	// random variables:
	//std::random_device dev;
	// random functions:
	int randomNumber() {
		static std::uniform_int_distribution<> dist(0, N_TYPE - 1);
		return dist(rng);
	}
	void at(tnode<N_TYPE>* root, entry*& word) {
		int randomTemp = randomNumber();
		// decide whether we choose word in this charater or continue traverse:
		// if randomNumber mod 3 = 1 we check value is exist or not and return the value;
		// else we traverse;

		if (randomTemp % 10 == 1) {
			if (root->value.empty() == false) {
				word = root->value.front().get();
				return;
			}
			
		}

		
		if (root->next[randomTemp] == nullptr) {
			if (root->value.empty() == false) {
				word = root->value.front().get();
				return;
			}
			else {
				while (true) {
					randomTemp = (randomTemp + 1) % N_TYPE;
					if (root->next[randomTemp] != nullptr) {
						break;
					}
				}
				at(root->next[randomTemp], word);
				return;
			}
		}
		else {
			at(root->next[randomTemp], word);
			return;
		}


	}
	//Copy the entire trie (deep copy, not just the pointers)
	tnode<N_TYPE>* copy(tnode<N_TYPE>* root) {
		if (!root) return nullptr;
		tnode<N_TYPE>* temp = new tnode<N_TYPE>();
		temp->key = root->key;
		temp->value = root->value;
		for (int i = 0; i < N_TYPE; ++i) {
			temp->next[i] = copy(root->next[i]);
		}
		return temp;
	}
public:
	trie() {
		root = new tnode<N_TYPE>();
		key_count = 0;
	}
	~trie() {
		delete root;
	}
	//Copy constructor
	trie(const trie<N_TYPE>& _source) {
		root = copy(_source.root); //copy the entire trie here
		key_count = _source.key_count;
		ASSIGN = _source.ASSIGN;
	}
	//Copy assignment
	trie<N_TYPE>& operator=(const trie<N_TYPE>& _source) {
		if (this != &_source) {
			delete root;
			root = copy(_source.root); //copy the entire trie here
			key_count = _source.key_count;
			ASSIGN = _source.ASSIGN;
		}
		return *this;
	}
	//Move constructor
	trie(trie<N_TYPE>&& _source) {
		root = _source.root;
		key_count = _source.key_count;
		_source.root = nullptr;
		_source.key_count = 0;
	}
	//Move assignment
	trie<N_TYPE>& operator=(trie<N_TYPE>&& _source) {
		if (this != &_source) {
			delete root;
			root = _source.root;
			key_count = _source.key_count;
			_source.root = nullptr;
			_source.key_count = 0;
		}
		return *this;
	}
	//Return the root node
	tnode<N_TYPE>*& top() {
		return root;
	}
	//Return the number of key inside the tree
	unsigned int count() {
		return key_count;
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
		}
		cur->value.push_back(entry);
		key_count++;
	}
	//Insert entry into the definition trie
	void insert_d(const shptr<entry>& entry) {
		tnode<N_TYPE>* cur = root;
		for (const auto& i : entry->value) {
			int j = index(i);
			if (!cur->next[j]) cur->next[j] = new tnode<N_TYPE>(i);
			cur = cur->next[j];
		}
		cur->value.push_back(entry);
		key_count++;
	}
	//Remove keyword from the keyword trie
	void remove(const std::string& key) {
		remove(this->root, key, 0);
		key_count--;
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

	// Random Functions:
	entry* random() {
		entry* word;
		at(root, word);
		return word;
	}
};