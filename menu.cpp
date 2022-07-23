#include "menu.hpp"

void choose_dictionary() {
	vector<dictionary_entry> temp;
	cout << "Choose dictionary data set: \n";
	ifstream fin(dictionary_path + (string)"list_of_dictionary.txt");
	string line,s;
	dictionary_entry x;
	while (getline(fin, line)) {
		stringstream ss(line);
		getline(ss, s, '`');
		x.filename = s;
		getline(ss, s);
		x.name = s;
		temp.push_back(x);
	}
	for (int i = 0; i < temp.size(); ++i) {
		cout << i + 1 << "." << temp[i].name << endl;
	}
	cout << "Please choose the dictionary you want to use: (1-" << temp.size() << "): ";
	int choose;
	cin >> choose;
	dictionary<ASCII, ASCII> dict(temp[choose - 1].filename, binary);
	enter_dictionary_menu(dict,temp[choose - 1].name);
	fin.close();
}

void enter_dictionary_menu(dictionary<ASCII, ASCII>& dict,string dict_name) {
	system("cls");
	cout << "WELCOME TO " << dict_name << "!!\n\n";
	cout << "Here is some task you can do with our dicitonary: \n";
	cout << "1. Search for a keyword.\n";
	cout << "2. Search for a definition.\n";
	cout << "3. View history of searched word.\n";
	cout << "4. Add new word and its definition.\n";
	cout << "5. Edit definition.\n";
	cout << "6. Remove a word.\n";
	cout << "7. Reset the dictionary.\n";
	cout << "8. View a random word.\n";
	cout << "9. View the favourite list.\n";
	cout << "10. Remove/add word from the fourvarite list.\n";
	cout << "11. Play awesomes games.\n";
	int choose;
}

void search_word(dictionary <ASCII, ASCII>& dict) {
	cout << "Enter the word you want to find: ";
	string s;
	cin >> s;
	entry* temp = dict.find_word(s);
	cout << "The word you want to find is: " << temp->key << ": " << temp->value << endl;
	cout << "Do you want this word to be your favourite word?(y/n)";
	cin >> s;
	if (s == "y") dict.addWordToFavourtite(temp);
}

void search_definition(dictionary <ASCII, ASCII>& dict) {
	cout << "Enter the word you want to find definition: ";
	string s;
	cin >> s;
	vector<entry*> temp = dict.find_definition(s);
	cout << "Here is the list of word match your definition:\n";
	for (auto i : temp) cout << i->key << endl;
	cout << "Do you want add any of these word to your favourite list?(y/n)";
	cin >> s;
	if (s == "y") {
		
	}
}

void add_word_menu(dictionary<ASCII, ASCII>& dict) {
	string word, def, temp;
	cout << "Enter the keyword: ";
	cin >> word;
	cout << "Enter the definition: ";
	cin >> def;
	dict.insert(word, def);
}

void remove_word_menu(dictionary<ASCII, ASCII>& dict) {
	string word, temp;
	cout << "Enter the word you want to remove: ";
	cin >> word;
	dict.remove(word);
}
