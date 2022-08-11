#pragma once
#include <vector>

template<typename T>
std::vector<T> vector_intersection(const std::vector<T>& vector1, const std::vector<T>& vector2) {
	auto iter1 = vector1.cbegin();
	auto iter2 = vector2.cbegin();
	std::vector<T> vectorOUT;
	while ((iter1 != vector1.cend()) && (iter2 != vector2.cend())) {
		if (*iter1 < *iter2) ++iter1;
		else {
			if (!(*iter2 < *iter1)) vectorOUT.push_back(*iter1++);
			++iter2;
		}
	}
	return vectorOUT;
}