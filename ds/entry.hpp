#pragma once
#include <string>

class entry {
public:
	std::string key;	//keyword
	std::string value; //definition
	entry(const std::string& key, const std::string& value);
};