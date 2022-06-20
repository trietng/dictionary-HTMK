#include "dictionary.hpp"

void dictionary::insert(const std::string& word, const std::string& definition) {
	sh_ptr<entry> ent(new entry(word, definition));
	this->word.insert(ent);
	this->definition.insert_def(ent);
}

void dictionary::remove(const std::string& word) {
	this->word.remove(word);
}

entry* dictionary::find_word(const std::string& word) {
	return this->word.find(word);
}

std::vector<entry*> dictionary::find_definition(const std::string& keyword) {
	return this->definition.find_def(keyword);
}