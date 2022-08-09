#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "entry.hpp"
#include "shptr.hpp"
#include "avl_tree.hpp"

class htable {
private:
	static constexpr size_t HASHTABLE_CAPACITY = 10e6;
	std::vector<avl_tree> data;
	size_t counter;
	size_t hash(const std::string& key);
	std::vector<std::string> get_words(const std::string& sentence);
public:
	htable();
	~htable();
	//Insert operation
	void insert(const std::string& key, const shptr<entry>& value);
	//Find operation
	std::vector<entry*> find(const std::string& key);
	//Remove operation
	void remove(const shptr<entry>& ent);
	//Clear
	void clear();
};