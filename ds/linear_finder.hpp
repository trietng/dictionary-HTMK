#pragma once
#include <string>
#include <vector>

class linear_finder {	
public:
	std::string* data;
	size_t last;
	linear_finder();
	~linear_finder();
	//Copy constructor
	linear_finder(const linear_finder& _source);
	//Copy assignment
	linear_finder& operator=(const linear_finder& _source);
	//Move constructor
	linear_finder(linear_finder&& _source) noexcept;
	//Move assignment
	linear_finder& operator=(linear_finder&& _source) noexcept;
	//Add new to the back
	void append(const std::string& word, const std::string& def);
	//Find the first occurrences of the , return a vector of word strings
	std::string find(const std::string& key);
	//Clear
	void clear();
};