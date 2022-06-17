#include "trie.hpp"

tnode::tnode() {
	key = '\0';
	for (int i = 0; i < 96; ++i) {
		next[i] = nullptr;
	}
	value = nullptr;
}

tnode::~tnode() {
	for (int i = 0; i < 96; ++i) {
		delete next[i];
	}
	delete value;
}

tnode::tnode(const char& key) {
	this->key = key;
	for (int i = 0; i < 96; ++i) {
		next[i] = nullptr;
	}
	value = nullptr;
}

int index_ascii(const char& key) {
	if (key == '\0') return 0;
	return (int)key - 31;
}

trie::trie() {
	root = new tnode();
}

trie::~trie() {
	delete root;
}

bool trie::is_leaf(tnode* node) {
	for (int i = 0; i < 96; ++i) {
		if (!node->next[i]) return false;
	}
	return true;
}
tnode* trie::remove(tnode* root, const std::string& key, const int& depth) {
	if (!root) return nullptr;
	if (depth == key.size()) {
		if (root->value) {
			delete root->value;
			root->value = nullptr;
		}
		if (is_leaf(root)) {
			delete root;
			root = nullptr;
		}
		return root;
	}
	int i = index_ascii(key[depth]);
	root->next[i] = remove(root->next[i], key, depth + 1);
	if (is_leaf(root) && !root->value) {
		delete root;
		root = nullptr;
	}
	return root;
}

void trie::insert(const std::string& key, const std::string& value) {
	tnode* cur = root;
	for (const auto& i : key) {
		int j = index_ascii(i);
		if (!cur->next[j]) cur->next[j] = new tnode(i);
		cur = cur->next[j];
	}
	cur->value = new std::string(value);
}

void trie::remove(const std::string& key) {
	remove(this->root, key, 0);
}

std::string* trie::find(const std::string& key) {
	tnode* cur = root;
	for (const auto& i : key) {
		int j = index_ascii(i);
		if (!cur->next[j]) return nullptr;
		cur = cur->next[j];
	}
	return cur->value;
}