#include "htable.hpp"

size_t htable::hash(const std::string& key) {
	uint32_t hash_res = 0;
	for (size_t i = 0; i < key.length(); i++) {
		hash_res += key[i] * pow(PRIME, i);
	}
	return hash_res;
}

std::vector<std::string> htable::get_words(const std::string& sentence) {
	std::stringstream ss(sentence);
	std::vector<std::string> vec;
	std::string word;
	while (getline(ss, word, ' ')) {
		for (int i = 0; i < word.length(); ++i) {
			if (!isalnum(word[i])) word.erase(i, 1);
		}
		for (char& ch : word) {
			ch = tolower(ch);
		}
		vec.push_back(word);
	}
	return vec;
}

htable::htable() {
	data.assign(HASHTABLE_CAPACITY, avl_tree());
	counter = 0;
}

htable::~htable() {
	data.clear();
	counter = 0;
}

void htable::insert(const std::string& definition, const shptr<entry>& value) {
	std::vector<std::string> key = get_words(definition);
	for (const auto& item : key) {
		size_t hash1 = hash(item);
		size_t hash2 = hash(value->key);
		data[hash1 % HASHTABLE_CAPACITY].insert(hash2, value);
	}
}

std::vector<entry*> htable::find(const std::string& key) {
	return data[hash(key) % HASHTABLE_CAPACITY].vector();
}

void htable::remove(const shptr<entry>& ent) {
	size_t hash1 = hash(ent->value);
	size_t hash2 = hash(ent->key);
	data[hash1 % HASHTABLE_CAPACITY].remove(hash2);
}

void htable::clear() {
	data.clear();
}
