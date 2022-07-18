#pragma once
#include "dictionary.hpp"

template <unsigned int N_WORD, unsigned int N_DEF>
void guess_definition_meaning(dictionary<N_WORD, N_DEF> dict) {
	vector <entry*> def;
	entry* temp;
	string guess_def;

	for (int i = 0; i < 4; i++) {
		temp = dict.find_rand_word();
		def.push_back(temp);
	}

	//choose one of 4 word to become a definition question:
	srand(time(nullptr));
	int tmp_ans = rand() % 4;
	guess_def = def[tmp_ans]->key;


	system("cls");
	cout << "AWESOME QUIZZES !" << endl;
	cout << "Can you guess a word from a definition? " << endl;
	cout << "There are four keyword to choose and one of them is correct" << endl;
	cout << guess_def << endl;
	cout << "And the key word is:" << endl;
	cout << "1/ " << def[0]->value << endl;
	cout << "2/ " << def[1]->value << endl;
	cout << "3/ " << def[2]->value << endl;
	cout << "4/ " << def[3]->value << endl;

	int tmp;
	cin >> tmp;

	if (def[tmp-1]->key == guess_def)
		cout << "CORRECT";
	else
		cout << "INCORRECT";

	cout << guess_def;
	return;
}
