#include "linear_finder.hpp"

linear_finder::linear_finder() {
	data = new std::string;
	last = 0;
}

linear_finder::~linear_finder() {
	delete data;
	data = nullptr;
	last = std::string::npos;
}

linear_finder::linear_finder(const linear_finder& _source) {
	data = new std::string(*(_source.data));
	last = _source.last;
}

linear_finder& linear_finder::operator=(const linear_finder& _source) {
	if (this != &_source) {
		delete data;
		data = new std::string(*(_source.data));
		last = _source.last;
	}
	return *this;
}

linear_finder::linear_finder(linear_finder&& _source) noexcept {
	data = _source.data;
	last = _source.last;
	delete _source.data;
	_source.data = nullptr;
	_source.last = std::string::npos;
}

linear_finder& linear_finder::operator=(linear_finder&& _source) noexcept {
	if (this != &_source) {
		data = _source.data;
		last = _source.last;
		delete _source.data;
		_source.data = nullptr;
		_source.last = std::string::npos;
	}
	return *this;
}

void linear_finder::append(const std::string& word, const std::string& def) {
	data->append(def + "\t" + word + "\n");
}

std::string linear_finder::find(const std::string& key) {
	size_t cache = last;
	last = data->find(key, last);
	if (last == std::string::npos) {
		if (cache > 0) {
			last = data->rfind(key, cache);
			if (last == std::string::npos) return ""; //worst case scenario
		}
		else {
			last = 0;
			return "";
		}
	}
	for (size_t i = last; i < data->size(); ++i) {
		if ((*data)[i] == '\t') {
			++i;
			size_t j = i;
			for (; (*data)[j] != '\n'; ++j) {
				//this is left empty intentionally
			}
			last = j;
			return data->substr(i, j - i); //best case scenario
		}
		else if ((*data)[i] == '\n') {
			last = i;
			last = data->find(key, last);
			if (last == std::string::npos) return "";
			i = last - 1;
			continue;
		}
	}
	return "";
}

void linear_finder::clear() {
	delete data;
	data = nullptr;
	last = 0;
}