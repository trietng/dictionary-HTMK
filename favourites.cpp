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

bool fav_word::remove(string i)
{
	if (vec.empty())
		return false;
	for (int j = 0; j < vec.size(); j++)
	{
		if (i == vec.at(j))
		{
			swap(vec[j], vec.back());
			vec.pop_back();
			return true;
		}
	}
	return false;
}

void fav_word::display()
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << i + 1 << ". " << vec[i] << endl;
	}
}

