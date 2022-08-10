#include "htable.hpp"

uint32_t htable::hash(const std::string& key) {
	uint32_t hash = 5381;
	for (const auto& ch : key) {
		hash = ((hash << 5) + hash) + ch;
	}
	return hash;
}

std::vector<std::string> htable::generate_alnum(const std::string& sentence) {
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

std::vector<entry*> htable::to_entry(const std::vector<avl_node*>& _avl_tree) {
	std::vector<entry*> result;
	result.reserve(_avl_tree.size());
	for (const auto& node : _avl_tree) {
		result.push_back(node->value.get());
	}
	return result;
}

htable::htable() {
	data.assign(HASHTABLE_CAPACITY, avl_tree());
	max_hash = 0;
	counter = 0;
}

htable::~htable() {
	data.clear();
	counter = 0;
}

void htable::insert(const std::string& definition, const shptr<entry>& value) {
	std::vector<std::string> key = generate_alnum(definition);
	for (const auto& item : key) {
		size_t hash1 = hash(item);
		size_t hash2 = hash(value->key);
		data[hash1 % HASHTABLE_CAPACITY].insert(hash1, hash2, value);
		++counter;
	}
}

std::vector<entry*> htable::find(const std::vector<std::string>& key) {
	std::vector<std::vector<avl_node*>> vec;
	for (const auto& item : key) {
		auto hash1 = hash(item);
		vec.push_back(data[hash1 % HASHTABLE_CAPACITY].vector(hash1));
	}
	if (vec.size() == 0) return std::vector<entry*>();
	else if (vec.size() == 1) return to_entry(vec.front());
	std::vector<avl_node*> intersection;
	intersection = vector_intersection(*(vec.cbegin()), *(vec.cbegin() + 1));
	for (auto it = vec.cbegin() + 2; it != vec.cend(); ++it) {
		intersection = vector_intersection(intersection, *it);
	}
	return to_entry(intersection);
}

void htable::remove(const std::string& definition) {
	std::vector<std::string> key = generate_alnum(definition);
	for (const auto& item : key) {
		size_t hash1 = hash(item);
		data[hash1 % HASHTABLE_CAPACITY].remove(hash1);
	}
}

void htable::clear() {
	data.clear();
	counter = 0;
}

size_t htable::max_capacity() const {
	return HASHTABLE_CAPACITY;
}

size_t htable::count() const {
	return counter;
}
