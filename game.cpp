#include "game.hpp"
#include "header.hpp"

bool checkDuplicate(vector<entry*> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (vec[i] == vec[j])
				return false;
		}
	}
	return true;
}

void guess_keyword_meaning(dictionary dict) {
	vector <entry*> def;
	entry* temp;
	string guess_def;

	for (int i = 0; i < 4; i++) {
		temp = dict.find_rand_word();
		def.push_back(temp);
		if (checkDuplicate(def) == false) {
			def.pop_back();
			i--;
		}
	}

	//choose one of 4 word to become a definition question:
	srand(time(nullptr));
	int tmp_ans = rand() % 4;
	guess_def = def[tmp_ans]->key;


	system("cls");
	cout << "AWESOME QUIZZES !" << endl;
	cout << "Can you guess a keyword from a definition? " << endl;
	cout << "There are four definitions to choose and one of them is correct" << endl;
	cout << guess_def << endl;
	cout << "And the definition is:" << endl;
	cout << "1/ " << def[0]->value << endl;
	cout << "2/ " << def[1]->value << endl;
	cout << "3/ " << def[2]->value << endl;
	cout << "4/ " << def[3]->value << endl;

	int tmp = 1;
	cin >> tmp;


	if (def[tmp - 1]->key == guess_def)
		cout << "CORRECT";
	else
		cout << "INCORRECT";

	cout << endl << def[tmp_ans]->value;

	cout << "\nPress any key to continue..." << endl;
	_getch();

	return;
}

void guess_definition_meaning(dictionary dict) {
	vector <entry*> def;
	entry* temp;
	string guess_def;

	for (int i = 0; i < 4; i++) {
		temp = dict.find_rand_word();
		def.push_back(temp);
		if (checkDuplicate(def) == false) {
			def.pop_back();
			i--;
		}
	}

	//choose one of 4 word to become a definition question:
	srand(time(nullptr));
	int tmp_ans = rand() % 4;
	guess_def = def[tmp_ans]->value;


	system("cls");
	cout << "AWESOME QUIZZES !" << endl;
	cout << "Can you guess a definition from a keyword? " << endl;
	cout << "There are four keywords to choose and one of them is correct" << endl;
	cout << guess_def << endl;
	cout << "And the keyword is:" << endl;
	cout << "1/ " << def[0]->key << endl;
	cout << "2/ " << def[1]->key << endl;
	cout << "3/ " << def[2]->key << endl;
	cout << "4/ " << def[3]->key << endl;

	int tmp = 1;
	cin >> tmp;
	

	if (def[tmp - 1]->value == guess_def)
		cout << "CORRECT";
	else
		cout << "INCORRECT";

	cout << endl << def[tmp_ans]->key;


	cout << "\nPress any key to continue..." << endl;
	_getch();
	
	return;


}


