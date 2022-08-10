#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "entry.hpp"
#include "shptr.hpp"
#include "avl_tree.hpp"

class htable {
private:
	static constexpr size_t HASHTABLE_CAPACITY = 13e6 + 19;
	std::vector<avl_tree> data;
	size_t counter;
	size_t max_hash;
	//djb2 hash function
	uint32_t hash(const std::string& key);
	//Generate alpha-numeric, single-words from the input string
	std::vector<std::string> generate_alnum(const std::string& sentence);
	//
	std::vector<entry*> to_entry(const std::vector<avl_node*>& _avl_tree);
public:
	htable();
	~htable();
	//Insert operation
	void insert(const std::string& definition, const shptr<entry>& value);
	//Find a set of words
	std::vector<entry*> find(const std::vector<std::string>& key);
	//Remove a key from the hashtable
	void remove(const std::string& definition);
	//Clear
	void clear();
	//Get capacity of the hash table
	size_t max_capacity() const;
	//Get the number of keys inside the hash table
	size_t count() const;
};