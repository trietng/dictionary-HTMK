#pragma once
#include <cstdint>
#include <cmath>
#include <vector>
#include <string>
#include "entry.hpp"
#include "shptr.hpp"

static constexpr size_t PRIME = 31;

uint16_t pmax(const uint16_t& x, const uint16_t& y);

class avl_node {
public:
	uint32_t key;
	shptr<entry> value;
	uint16_t height;
	avl_node* left;
	avl_node* right;
	avl_node();
	avl_node(const uint32_t& key, const shptr<entry>& value);
	~avl_node();
};

class avl_tree {
private:
	avl_node* root;
	uint32_t hash(const std::string& key);
	//Return the height of the node
	uint16_t height(avl_node* node);
	//Right rotation
	avl_node* right_rotate(avl_node* node);
	//Left rotation
	avl_node* left_rotate(avl_node* node);
	//Return the difference between the heights of the two children
	int16_t difference(avl_node* node);
	//Return the leftmost child
	avl_node* leftmost(avl_node* node);
	//Private recursive insertion operation
	avl_node* insert(avl_node* root, const uint32_t& key, const shptr<entry>& value);
	//Private recursive removal operation
	avl_node* remove(avl_node* root, const uint32_t& key);
	//Private recursive get vector operation
	void vector(avl_node* root, std::vector<entry*>& vec);
	//Copy the entire tree (deep copy, not just the pointers)
	avl_node* copy(avl_node* root);
public:
	avl_tree();
	~avl_tree();
	//Copy constructor
	avl_tree(const avl_tree& _source);
	//Copy assignment
	avl_tree& operator=(const avl_tree& _source);
	//Move constructor
	avl_tree(avl_tree&& _source) noexcept;
	//Move assignment
	avl_tree& operator=(avl_tree&& _source) noexcept;
	//Insert raw key and value into the AVL tree
	void insert(const std::string& key, const shptr<entry>& value);
	//Remove raw key from the AVL tree
	void remove(const std::string& key);
	//Insert hashed key and raw value into the AVL tree
	void insert(const uint32_t& key, const shptr<entry>& value);
	//Remove hashed key from the AVL tree
	void remove(const uint32_t& key);
	//Get the entire tree as vector
	std::vector<entry*> vector();
};