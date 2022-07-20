#include "favourites.hpp"
#include "ds\trie.hpp"

fav_word::fav_word()
{
	ifstream fin;
	fin.open(favourite_output);
	int n;
	string s;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		fin >> s;
		vec.push_back(s);
	}
	fin.close();
}

fav_word::~fav_word()
{
	ofstream fout(favourite_output);
	fout << vec.size() << endl;
	for (auto i : vec) cout << i << " ";
	fout.close();
}

void fav_word::mark(entry* ent)
{
	vec.push_back(ent->key);
}

void fav_word::remove(string s)
{
	if (vec.empty())
		return;
	for (int i = 0; i < vec.size(); j++)
	{
		if (s == vec.at(i))
		{
			vec.erase(vec[i]);
			return;
		}
	}
}

void fav_word::display()
{
	for (auto i:vector)
	{
		cout << "Favourite list: \n";
		cout << i + 1 << ". " << vec[i] << endl;
	}
}

