#pragma once
#include <string>

class tnode {
public:
	char key;
	tnode* next[96];
	std::string* value;
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
	//Insert key into the trie
	void insert(const std::string& key, const std::string& value);
	//Remove key from the trie
	void remove(const std::string& key);
	//Find key inside the trie
	std::string* find(const std::string& key);
};