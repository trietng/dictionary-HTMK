#include "avl_tree.hpp"

uint16_t pmax(const uint16_t& x, const uint16_t& y) {
	return (x > y) ? x : y;
}

avl_node::avl_node() {
	this->key = UINT32_MAX;
	this->height = 1;
	this->left = this->right = nullptr;
}

avl_node::avl_node(const uint32_t& key, const shptr<entry>& value) {
	this->key = key;
	this->value = value;
	this->height = 1;
	this->left = this->right = nullptr;
}

avl_node::~avl_node() {
	delete left;
	delete right;
}

uint32_t avl_tree::hash(const std::string& key) {
	uint32_t hash_res = 0;
	for (size_t i = 0; i < key.length(); i++) {
		hash_res += key[i] * pow(PRIME, i);
	}
	return hash_res;
}

uint16_t avl_tree::height(avl_node* node) {
	return (node) ? node->height : 0;
}

avl_node* avl_tree::right_rotate(avl_node* node) {
	/*
	Right rotation illustration
			3 {node}        2
		   / \             / \
		  2 {top}      ->     3
		 / \                 / \
			1 {bottom}      1
	*/
	avl_node* top = node->left;
	avl_node* bottom = top->right;
	top->right = node;
	node->left = bottom;
	node->height = pmax(height(node->left), height(node->right)) + 1;
	top->height = pmax(height(top->left), height(top->right)) + 1;
	return top;
}

avl_node* avl_tree::left_rotate(avl_node* node) {
	avl_node* top = node->right;
	avl_node* bottom = top->left;
	top->left = node;
	node->right = bottom;
	node->height = pmax(height(node->left), height(node->right)) + 1;
	top->height = pmax(height(top->left), height(top->right)) + 1;
	return top;
}

int16_t avl_tree::difference(avl_node* node) {
	return (node) ? (height(node->left) - height(node->right)) : 0;
}

avl_node* avl_tree::leftmost(avl_node* node) {
	if (!node) return nullptr;
	avl_node* cur = node;
	while (cur->left) {
		cur = cur->left;
	}
	return cur;
}

avl_node* avl_tree::insert(avl_node* root, const uint32_t& key, const shptr<entry>& value) {
	if (!root) return new avl_node(key, value);
	else if (key < root->key) root->left = insert(root->left, key, value);
	else if (key > root->key) root->right = insert(root->right, key, value);
	else return root;
	root->height = pmax(height(root->left), height(root->right)) + 1;
	auto d = difference(root);
	if (d > 1) {
		//TRUE: LEFT RIGHT, FALSE: LEFT LEFT
		if (key > root->left->key) root->left = left_rotate(root->left);
		return right_rotate(root);
	}
	if (d < -1) {
		//TRUE: RIGHT LEFT, FALSE: RIGHT RIGHT
		if (key < root->right->key) root->right = right_rotate(root->right);
		return left_rotate(root);
	}
	return root;
}

avl_node* avl_tree::remove(avl_node* root, const uint32_t& key) {
	if (!root) return root;
	else if (key < root->key) root->left = remove(root->left, key);
	else if (key > root->key) root->right = remove(root->right, key);
	else {
		if ((!root->left) || (!root->right)) {
			avl_node* child = (root->left) ? (root->left) : (root->right);
			if (child) {
				*root = *child;
			}
			else {
				child = root;
				root = nullptr;
			}
			delete child;
		}
		else {
			avl_node* tmp = leftmost(root->right);
			root->key = tmp->key;
			root->value = tmp->value;
			root->right = remove(root->right, tmp->key);
		}
	}
	if (!root) return root;
	root->height = pmax(height(root->left), height(root->right)) + 1;
	int d = difference(root);
	if (d > 1) {
		//TRUE: LEFT RIGHT, FALSE: LEFT LEFT
		if (difference(root->left) < 0) root->left = left_rotate(root->left);
		return right_rotate(root);
	}
	if (d < -1) {
		//TRUE: RIGHT LEFT, FALSE: RIGHT RIGHT
		if (difference(root->right) > 0) root->right = right_rotate(root->right);
		return left_rotate(root);
	}
	return root;
}

void avl_tree::vector(avl_node* root, std::vector<entry*>& vec) {
	if (!root) return;
	vector(root->left, vec);
	vector(root->right, vec);
	std::cout << root->value.get()->key;
	vec.push_back(root->value.get());
}

avl_node* avl_tree::copy(avl_node* root) {
	if (!root) return nullptr;
	avl_node* temp = new avl_node();
	temp->key = root->key;
	temp->value = root->value;
	temp->height = root->height;
	temp->left = copy(root->left);
	temp->right = copy(root->right);
	return temp;
}

avl_tree::avl_tree() {
	root = nullptr;
}

avl_tree::~avl_tree() {
	delete root;
}

avl_tree::avl_tree(const avl_tree& _source) {
	root = copy(_source.root);
}

avl_tree& avl_tree::operator=(const avl_tree& _source) {
	if (this != &_source) {
		delete root;
		root = copy(_source.root);
	}
	return *this;
}

avl_tree::avl_tree(avl_tree&& _source) noexcept {
	root = _source.root;
	_source.root = nullptr;
}

avl_tree& avl_tree::operator=(avl_tree&& _source) noexcept {
	if (this != &_source) {
		delete root;
		root = _source.root;
		_source.root = nullptr;
	}
	return *this;
}

void avl_tree::insert(const std::string& key, const shptr<entry>& value) {
	root = insert(root, hash(key), value);
}

void avl_tree::remove(const std::string& key) {
	root = remove(root, hash(key));
}

void avl_tree::insert(const uint32_t& key, const shptr<entry>& value) {
	root = insert(root, key, value);
}

void avl_tree::remove(const uint32_t& key) {
	root = remove(root, key);
}

std::vector<entry*> avl_tree::vector() {
	std::vector<entry*> result;
	vector(root, result);
	return result;
}