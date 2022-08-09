#include "trie.hpp"

std::string tolower(const std::string& _source) {
	std::string temp = _source;
	for (auto& ch : temp) {
		ch = tolower(ch);
	}
	return temp;
}
    
tnode::tnode() {
	this->key = '\0';
	this->SIZE = 0;
	this->next = nullptr;
}
tnode::tnode(const uint8_t& SIZE) {
	this->key = '\0';
	this->SIZE = SIZE;
	this->next = new tnode * [SIZE];
	for (uint8_t i = 0; i < SIZE; ++i) {
		this->next[i] = nullptr;
	}
}
tnode::tnode(const uint8_t& SIZE, const char& key) {
	this->key = key;
	this->SIZE = SIZE;
	this->next = new tnode * [SIZE];
	for (uint8_t i = 0; i < SIZE; ++i) {
		this->next[i] = nullptr;
	}
}
tnode::~tnode() {
	for (uint8_t i = 0; i < SIZE; ++i) {
		delete next[i];
	}
	delete next;
	SIZE = 0;
}

unsigned int trie::index(const char& key) {
	return (unsigned int)key - (unsigned int)offset;
}
// convert from index to char:
char trie::getCharFromIndex(const unsigned int& index) {
	return (char)('\0' + index + offset);
}
//Check if a node has any child
bool trie::is_leaf(tnode* node) {
	for (unsigned int i = 0; i < N_TYPE; ++i) {
		if (!node->next[i]) return false;
	}
	return true;
}
//Private recursive remove function
tnode* trie::remove(tnode* root, const std::string& key, const int& depth) {
	if (!root) return nullptr;
	if (depth == key.size()) {
		if (!root->value.empty()) {
			root->value.clear();
		}
		if (is_leaf(root)) {
			delete root;
			root = nullptr;
		}
		return root;
	}
	int i = index(key[depth]);
	root->next[i] = remove(root->next[i], key, depth + 1);
	if (is_leaf(root) && root->value.empty()) {
		delete root;
		root = nullptr;
	}
	return root;
}

int trie::randomNumber() {
	static std::uniform_int_distribution<> dist(0, N_TYPE - 1);
	return dist(rng);
}
void trie::at(tnode* root, entry*& word) {
	int randomTemp = randomNumber();
	// decide whether we choose word in this charater or continue traverse:
	// if randomNumber mod 3 = 1 we check value is exist or not and return the value;
	// else we traverse;

	if (randomTemp % 5 == 1) {
		if (root->value.empty() == false) {
			word = root->value.front().get();
			return;
		}

	}


	if (root->next[randomTemp] == nullptr) {
		if (root->value.empty() == false) {
			word = root->value.front().get();
			return;
		}
		else {
			while (true) {
				randomTemp = (randomTemp + 1) % N_TYPE;
				if (root->next[randomTemp] != nullptr) {
					break;
				}
			}
			at(root->next[randomTemp], word);
			return;
		}
	}
	else {
		at(root->next[randomTemp], word);
		return;
	}


}

tnode* trie::copy(tnode* root) {
	if (!root) return nullptr;
	tnode* temp = new tnode(N_TYPE);
	temp->key = root->key;
	temp->value = root->value;
	for (uint8_t i = 0; i < N_TYPE; ++i) {
		temp->next[i] = copy(root->next[i]);
	}
	return temp;
}

trie::trie() {
	root = nullptr;
	N_TYPE = 0;
	offset = UINT8_MAX;
	key_count = 0;
}

trie::trie(const uint8_t& N_TYPE) {
	root = new tnode(N_TYPE);
	this->N_TYPE = N_TYPE;
	offset = (N_TYPE == ASCII) ? 32 : 97;
	key_count = 0;
}
trie::~trie() {
	delete root;
	root = nullptr;
	N_TYPE = 0;
	offset = UINT8_MAX;
	key_count = 0;
}

trie::trie(const trie& _source) {
	N_TYPE = _source.N_TYPE;
	root = copy(_source.root); //copy the entire trie here
	offset = _source.offset;
	key_count = _source.key_count;
}

trie& trie::operator=(const trie& _source) {
	if (this != &_source) {
		delete root;
		N_TYPE = _source.N_TYPE;
		root = copy(_source.root); //copy the entire trie here
		offset = _source.offset;
		key_count = _source.key_count;
	}
	return *this;
}

trie::trie(trie&& _source) noexcept {
	N_TYPE = _source.N_TYPE;
	root = _source.root;
	offset = _source.offset;
	key_count = _source.key_count;
	_source.root = nullptr;
	_source.N_TYPE = 0;
	_source.offset = UINT8_MAX;
	_source.key_count = 0;
}

trie& trie::operator=(trie&& _source) noexcept {
	if (this != &_source) {
		delete root;
		N_TYPE = _source.N_TYPE;
		root = _source.root;
		offset = _source.offset;
		key_count = _source.key_count;
		_source.root = nullptr;
		_source.N_TYPE = 0;
		_source.offset = UINT8_MAX;
		_source.key_count = 0;
	}
	return *this;
}

tnode*& trie::top() {
	return root;
}

void trie::assign_count(const unsigned int& _key_count) {
	if (key_count == 0) key_count = _key_count;
}

unsigned int trie::count() {
	return key_count;
}

void trie::clear() {
	delete root;
	root = new tnode(N_TYPE);
}

void trie::insert(const shptr<entry>& entry) {
	tnode* cur = root;
	std::string temp = tolower(entry->key);
	for (const auto& i : temp) {
		int j = index(i);
		if (!cur->next[j]) cur->next[j] = new tnode(N_TYPE, i);
		cur = cur->next[j];
	}
	cur->value.push_back(entry);
	key_count++;
}

void trie::remove(const std::string& key) {
	std::string temp = tolower(key);
	remove(this->root, temp, 0);
	key_count--;
}

entry* trie::find(const std::string& key) {
	if (key.empty()) return nullptr;
	tnode* cur = root;
	std::string temp = tolower(key);
	for (const auto& i : temp) {
		int j = index(i);
		if (!cur->next[j]) return nullptr;
		cur = cur->next[j];
	}
	return (cur->value.empty()) ? nullptr : cur->value.front().get();
}

entry* trie::random() {
	entry* word;
	at(root, word);
	return word;
}