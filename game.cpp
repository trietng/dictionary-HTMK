#include "game.hpp"

bool checkDuplicate(vector<entry*> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (vec[i] == vec[j])
				return false;
		}
	}
	return true;
}