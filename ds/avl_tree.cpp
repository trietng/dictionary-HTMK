#include "avl_tree.hpp"

avl_node::avl_node() {
	this->hash1 = UINT32_MAX;
	this->hash2 = UINT32_MAX;
	this->height = 1;
	this->left = this->right = nullptr;
}

avl_node::avl_node(const uint32_t& hash1, const uint32_t& hash2, const shptr<entry>& value) {
	this->hash1 = hash1;
	this->hash2 = hash2;
	this->value = value;
	this->height = 1;
	this->left = this->right = nullptr;
}

avl_node::~avl_node() {
	delete left;
	delete right;
}

uint32_t avl_tree::hash(const std::string& key) {
	uint32_t hash = 5381;
	for (const auto& ch : key) {
		hash = ((hash << 5) + hash) + ch;
	}
	return hash;
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
	node->height = std::max(height(node->left), height(node->right)) + 1;
	top->height = std::max(height(top->left), height(top->right)) + 1;
	return top;
}

avl_node* avl_tree::left_rotate(avl_node* node) {
	avl_node* top = node->right;
	avl_node* bottom = top->left;
	top->left = node;
	node->right = bottom;
	node->height = std::max(height(node->left), height(node->right)) + 1;
	top->height = std::max(height(top->left), height(top->right)) + 1;
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

avl_node* avl_tree::insert(avl_node* root, const uint32_t& hash1, const uint32_t& hash2, const shptr<entry>& value) {
	if (!root) return new avl_node(hash1, hash2, value);
	else if (hash2 < root->hash2) root->left = insert(root->left, hash1, hash2, value);
	else if (hash2 > root->hash2) root->right = insert(root->right, hash1, hash2, value);
	else return root;
	root->height = std::max(height(root->left), height(root->right)) + 1;
	auto d = difference(root);
	if (d > 1) {
		//TRUE: LEFT RIGHT, FALSE: LEFT LEFT
		if (hash2 > root->left->hash2) root->left = left_rotate(root->left);
		return right_rotate(root);
	}
	if (d < -1) {
		//TRUE: RIGHT LEFT, FALSE: RIGHT RIGHT
		if (hash2 < root->right->hash2) root->right = right_rotate(root->right);
		return left_rotate(root);
	}
	return root;
}

avl_node* avl_tree::remove(avl_node* root, const uint32_t& hash2) {
	if (!root) return root;
	else if (hash2 < root->hash2) root->left = remove(root->left, hash2);
	else if (hash2 > root->hash2) root->right = remove(root->right, hash2);
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
			root->hash1 = tmp->hash1;
			root->hash2 = tmp->hash2;
			root->value = tmp->value;
			root->right = remove(root->right, tmp->hash2);
		}
	}
	if (!root) return root;
	root->height = std::max(height(root->left), height(root->right)) + 1;
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

void avl_tree::vector(avl_node* root, std::vector<avl_node*>& vec) {
	if (!root) return;
	vector(root->left, vec);
	vec.push_back(root);
	vector(root->right, vec);
}

void avl_tree::vector(avl_node* root, std::vector<avl_node*>& vec, const uint64_t& hash1) {
	if (!root) return;
	vector(root->left, vec);
	if (root->hash1 == hash1) vec.push_back(root);
	vector(root->right, vec);
}

void avl_tree::inversed_vector(avl_node* root, std::vector<avl_node*>& vec, const uint64_t& hash1) {
	if (!root) return;
	vector(root->left, vec);
	if (root->hash1 != hash1) {
		avl_node* tmp = new avl_node;
		tmp->hash1 = root->hash1;
		tmp->hash2 = root->hash2;
		tmp->height = UINT16_MAX;
		tmp->left = nullptr;
		tmp->right = nullptr;
		tmp->value = root->value;
		vec.push_back(tmp);
	}
	vector(root->right, vec);
}

avl_node* avl_tree::copy(avl_node* root) {
	if (!root) return nullptr;
	avl_node* temp = new avl_node();
	temp->hash1 = root->hash1;
	temp->hash2 = root->hash2;
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

void avl_tree::insert(const std::string& definition, const std::string& word, const shptr<entry>& value) {
	root = insert(root, hash(definition), hash(word), value);
}

void avl_tree::insert(const uint32_t& hash1, const uint32_t& hash2, const shptr<entry>& value) {
	root = insert(root, hash1, hash2, value);
}

void avl_tree::remove(const uint32_t& hash1) {
	std::vector<avl_node*> temp;
	inversed_vector(root, temp, hash1);
	clear();
	for (const auto& item : temp) {
		root = insert(root, item->hash1, item->hash2, item->value);
	}
}

std::vector<avl_node*> avl_tree::vector() {
	std::vector<avl_node*> result;
	vector(root, result);
	return result;
}

std::vector<avl_node*> avl_tree::vector(const uint32_t& hash1) {
	std::vector<avl_node*> result;
	vector(root, result, hash1);
	return result;
}

void avl_tree::clear() {
	delete root;
	root = nullptr;
}

template<>
std::vector<avl_node*> vector_intersection(const std::vector<avl_node*>& vector1, const std::vector<avl_node*>& vector2) {
	auto iter1 = vector1.cbegin();
	auto iter2 = vector2.cbegin();
	std::vector<avl_node*> vectorOUT;
	while ((iter1 != vector1.cend()) && (iter2 != vector2.cend())) {
		if ((*iter1)->hash2 < (*iter2)->hash2) ++iter1;
		else {
			if (!((*iter2)->hash2 < (*iter1)->hash2)) vectorOUT.push_back(*iter1++);
			++iter2;
		}
	}
	return vectorOUT;
}