#pragma once
#include <cstdint>
#include <cmath>
#include <vector>
#include <string>
#include "flist.hpp"
#include "entry.hpp"
#include "shptr.hpp"
#include "algorithm.hpp"

class avl_node {
public:
	uint32_t hash1;
	uint32_t hash2;
	shptr<entry> value;
	uint16_t height;
	avl_node* left;
	avl_node* right;
	avl_node();
	avl_node(const uint32_t& hash1, const uint32_t& hash2, const shptr<entry>& value);
	~avl_node();
};

class avl_tree {
private:
	avl_node* root;
	//djb2 hash function
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
	avl_node* insert(avl_node* root, const uint32_t& hash1, const uint32_t& hash2, const shptr<entry>& value);
	//Private recursive removal operation !!NOT USED!!
	avl_node* remove(avl_node* root, const uint32_t& hash2);
	//Remove hashed key from the AVL tree !!NOT USED!!
	void remove(const uint32_t& hash2);
	//Private recursive get vector operation, inorder traversal
	void vector(avl_node* root, std::vector<avl_node*>& vec);
	//Private recursive get vector operation, inorder traversal, specific key required
	void vector(avl_node* root, std::vector<avl_node*>& vec, const uint32_t& hash1);
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
	void insert(const std::string& definition, const std::string& word, const shptr<entry>& value);
	//Insert hashed key and raw value into the AVL tree
	void insert(const uint32_t& hash1, const uint32_t& hash2, const shptr<entry>& value);
	//Get the entire tree as vector
	std::vector<avl_node*> vector();
	//Get the entire tree as vector, specific key required
	std::vector<avl_node*> vector(const uint32_t& hash1);
	//Clear the entire tree
	void clear();
};

template<>
std::vector<avl_node*> vector_intersection(const std::vector<avl_node*>& vector1, const std::vector<avl_node*>& vector2);