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

fav_word::~fav_word()
{
	ofstream fout(favouriteFilepath);
	for (auto i : vec) cout << i.key << "`" << i.value;
	fout.close();
}

void fav_word::mark(entry ent)
{
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
	for (int i = 0; i < vec.size();++i)
	{
		cout << "Favourite list: \n";
		cout << i + 1 << ". " << vec[i].key << vec[i].value << endl;
	}
}

void fav_word::clear() {
	vec.clear();
	favouriteFilepath.clear();
}
