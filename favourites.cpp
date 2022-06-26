#include "favourites.hpp"
#include "ds\trie.hpp"
void fav_word::mark(entry* ent)
{
	vec.push_back(ent->key);
}

void fav_word::save()
{
	ofstream fout;
	fout.open(favourite_output);
	if(fout.is_open())
		for (auto i : vec)	fout << i << endl;
	else
	{
		cout << "Failed to open file!";
		system("pause");
	}
	fout.close();
}
fav_word::fav_word()
{
	ifstream fin;
	fin.open(favourite_output);
	if (!fin.is_open())
	{
		cout << "Failed to open file";
		system("pause");
		return;
	}
	while (!fin.eof())
	{
		string i;
		fin >> i;
		;
		vec.push_back(i);
	}
	fin.close();
}

