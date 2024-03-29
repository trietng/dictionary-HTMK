#include "favourites.hpp"
#include "ds\trie.hpp"


fav_word loadFavourite(string filename) {
	fav_word temp;
	temp.favouriteFilepath = favourite_output + filename + ".txt";
	ifstream fin(temp.favouriteFilepath);
	if (fin) {
		string ss, line, s, s1;
		while (getline(fin, line)) {
			stringstream ss(line);
			getline(ss, s, '`');
			getline(ss, s1);
			entry word(s, s1);
			temp.vec.push_back(word);
		}
	}
	return temp;
	fin.close();
}

void fav_word::write()
{
	ofstream fout(favouriteFilepath);
	for (auto i : vec) fout << i.key << "`" << i.value << endl;
	fout.close();
}

void fav_word::mark(entry ent)
{	
	for (int i = 0; i < vec.size(); ++i) if (compare_entry(ent, vec[i])) return;
	vec.push_back(ent);
}

void fav_word::remove(entry ent)
{
	if (vec.empty())
		return;
	for (int i = 0; i < vec.size(); i++)
	{
		if (compare_entry(ent,vec[i]))
		{
			vec.erase(vec.begin() + i);
			return;
		}
	}
}

bool compare_entry(entry x, entry y) {
	if (x.key == y.key && y.value == x.value) return true;
	return false;
}

void fav_word::display()
{	
	if (vec.empty()) cout << "You haven't had any favourite word!";
	else {
		cout << "Favourite list: \n";
		for (int i = 0; i < vec.size(); ++i)
		{
			cout << i + 1 << "." << vec[i].key << " MEANS " << vec[i].value << endl;
		}
	}
}

bool fav_word::isFavourite(string word) {
	for (auto i : vec) if (i.key == word) return true;
	return false;
}

void fav_word::clear() {
	vec.clear();
	favouriteFilepath.clear();
}
