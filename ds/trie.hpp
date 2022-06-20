#pragma once
#include <string>
#include "sh_ptr.hpp"
#include "cqueue.hpp"

class entry {
public:
	std::string key;
	std::string value;
	entry(const std::string& key, const std::string& value);
};

class tnode {
public:
	char key;
	tnode* next[96];
	cqueue<sh_ptr<entry>> value;
	tnode();
	tnode(const char& value);
	~tnode();
};

int index_ascii(const char& key);

class trie {
private:
	tnode* root;
	//Check if a node has any child
	bool is_leaf(tnode* node);
	//Private recursive remove function
	tnode* remove(tnode* root, const std::string& key, const int& depth);
public:
	trie();
	~trie();
	//Insert keyword into the keyword trie
	void insert(sh_ptr<entry> entry);
	//Insert definition into the definition trie
	void insert_def(sh_ptr<entry> entry);
	//Remove keyword from the keyword trie
	void remove(const std::string& key);
	//Find keyword inside the keyword trie
	entry* find(const std::string& key);
	//Find definition insert the definition trie
	std::vector<entry*> find_def(const std::string& def);
};