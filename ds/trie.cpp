#include "trie.hpp"

tnode::tnode() {
	key = '\0';
	for (int i = 0; i < 96; ++i) {
		next[i] = nullptr;
	}
}

tnode::~tnode() {
	for (int i = 0; i < 96; ++i) {
		delete next[i];
	}
}

tnode::tnode(const char& key) {
	this->key = key;
	for (int i = 0; i < 96; ++i) {
		next[i] = nullptr;
	}
}

entry::entry(const std::string& key, const std::string& value) {
	this->key = key;
	this->value = value;
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
		if (!root->value.empty()) {
			root->value.front()->key = "";
			root->value.pop_front();
		}
		if (is_leaf(root)) {
			delete root;
			root = nullptr;
		}
		return root;
	}
	int i = index_ascii(key[depth]);
	root->next[i] = remove(root->next[i], key, depth + 1);
	if (is_leaf(root) && root->value.empty()) {
		delete root;
		root = nullptr;
	}
	return root;
}

void trie::insert(sh_ptr<entry> entry) {
	tnode* cur = root;
	for (const auto& i : entry->key) {
		int j = index_ascii(i);
		if (!cur->next[j]) cur->next[j] = new tnode(i);
		cur = cur->next[j];
	}
	cur->value.push_back(entry);
}

void trie::insert_def(sh_ptr<entry> entry) {
	tnode* cur = root;
	for (int i = 0; i < entry->value.size(); ++i) {
		if (entry->value[i] == ' ') cur->value.push_back(entry);
		int j = index_ascii(entry->value[i]);
		if (!cur->next[j]) cur->next[j] = new tnode(entry->value[i]);
		cur = cur->next[j];
	}
	cur->value.push_back(entry);
}

void trie::remove(const std::string& key) {
	remove(this->root, key, 0);
}

entry* trie::find(const std::string& key) {
	tnode* cur = root;
	for (const auto& i : key) {
		int j = index_ascii(i);
		if (!cur->next[j]) return nullptr;
		cur = cur->next[j];
	}
	return cur->value.front().get();
}

std::vector<entry*> trie::find_def(const std::string& def) {
	std::vector<entry*> vt;
	tnode* cur = root;
	for (const auto& i : def) {
		int j = index_ascii(i);
		if (!cur->next[j]) return vt;
		cur = cur->next[j];
	}
	for (auto i = cur->value.cbegin(); i != nullptr; ++i) {
		if (((*i)->value.find(def) != std::string::npos) && ((*i)->key != "")) {
			vt.push_back((*i).get());
		}
	}
	return vt;
}