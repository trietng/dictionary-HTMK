#pragma once
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "nqueue.hpp"
#include "shptr.hpp"

static constexpr uint8_t ASCII = 95;
static constexpr uint8_t ALPHA = 26;
static std::random_device rd;
static std::mt19937 rng{rd()};

std::string tolower(const std::string& _source);

class entry {
public:
	std::string key;	//keyword
	std::string value; //definition
	entry(const std::string& key, const std::string& value);
};

class tnode {
public:
	char key; //1 bytes
	tnode** next; //8 bytes
	uint8_t SIZE; //1 bytes
	nqueue<shptr<entry>> value;
	tnode();
	tnode(const uint8_t& SIZE);
	tnode(const uint8_t& SIZE, const char& key);
	~tnode();
};

class trie {
private:
	tnode* root; // root node
	uint8_t N_TYPE; // type of trie
	uint8_t offset; // offset value to assign character
	unsigned int key_count; // count word in trie to randoms
	// get index of a node
	unsigned int index(const char& key);
	// convert from index to char:
	char getCharFromIndex(const unsigned int& index);
	//Check if a node has any child
	bool is_leaf(tnode* node);
	//Private recursive remove function
	tnode* remove(tnode* root, const std::string& key, const int& depth);
	int randomNumber();
	void at(tnode* root, entry*& word);
	//Copy the entire trie (deep copy, not just the pointers)
	tnode* copy(tnode* root);
public:
	trie();
	trie(const uint8_t& N_TYPE);
	~trie();
	//Copy constructor
	trie(const trie& _source);
	//Copy assignment
	trie& operator=(const trie& _source);
	//Move constructor
	trie(trie&& _source) noexcept;
	//Move assignment
	trie& operator=(trie&& _source) noexcept;
	//Return the root node
	tnode*& top();
	//Assign a value to key count
	void assign_count(const unsigned int& _key_count);
	//Return the number of key inside the tree
	unsigned int count();
	void clear();
	//Insert entry into the word trie
	void insert(const shptr<entry>& entry);
	//Remove keyword from the keyword trie
	void remove(const std::string& key);
	//Find keyword inside the keyword trie
	entry* find(const std::string& key);
	// Random Functions:
	entry* random();
};