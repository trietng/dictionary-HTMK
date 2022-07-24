#include "menu.hpp"

void choose_dictionary() {
	vector<string> list_of_file = get_list_of_files(dictionary_path);
	vector<string> dict_name;
	for (auto i : list_of_file) dict_name.push_back(get_dict_name(i));
	cout << "Welcome to our dictionary!\n";
	cout << "Here is the list of dictionary:\n";
	for (int i = 0; i < dict_name.size(); ++i) cout <<
		i + 1 << ". " << dict_name[i] << ".\n";
	cout << "Please choose the dictionary: ";
	int choose;
	cin >> choose;
	enter_dictionary_menu(dict_name[choose -  1],list_of_file[choose - 1]);
	
}

void enter_dictionary_menu(string& name,string& path) {
	system("cls");
	dictionary dict(path, binary);
	cout << "WELCOME TO " << name << "!\n";
	cout << "Here is some task you can do with our dicitonary: \n";
	cout << "1. Search for a keyword.\n";
	cout << "2. Search for a definition.\n";
	cout << "3. View history of search words.\n";
	cout << "4. Add new word and its definition.\n";
	cout << "5. Edit definition.\n";
	cout << "6. Remove a word.\n";
	cout << "7. Reset the dictionary.\n";
	cout << "8. View a random word.\n";
	cout << "9. View the favourite list.\n";
	cout << "10. Guess definition game.\n";
	cout << "11. Guess word game.\n";
	cout << "Your choice: ";
	int choose;
	cin >> choose;
	cout << endl;
	switch (choose) {
	case 1:search_word(dict);
		break;
	case 2:search_definition(dict);
		break;
	case 3: dict.seeHistory();
		break;
	case 4:add_word_menu(dict);
		break;
	case 5:edit_def_menu(dict);
		break;
	case 6:remove_word_menu(dict);
		break;
	case 7: dict.restore();
		break;
	case 8: 
		dict.print_random_word();
		break;
	case 9:dict.seeFavourite();
		break;
	case 10:guess_definition_meaning(dict);
		break;
	case 11:guess_keyword_meaning(dict);
	}
	dict.write();
}

void search_word(dictionary& dict) {
	cout << "Enter the word you want to find: ";
	string s;
	cin >> s;
	entry* temp = dict.find_word(s);
	cout << "The word you want to find is: " << temp->key << " MEANS " << temp->value << endl;
	cout << "Do you want this word to be your favourite word?(y/n)";
	cin >> s;
	if (s == "y") dict.addWordToFavourtite(temp);
}

void search_definition(dictionary& dict) {
	cout << "Enter the word you want to find definition: ";
	string s;
	cin >> s;
	vector<entry*> temp = dict.find_definition(s);
	cout << "Here is the list of word match your definition:\n";
	for (int i = 0; i < temp.size(); ++i) cout << i + 1 << ". " << temp[i]->key << " " << temp[i]->value << endl;
}

void edit_def_menu(dictionary& dict) {
	cout << "Enter the word you want to change definition:";
	string word;
	cin >> word;
	cout << "Enter new definition: ";
	string newdef;
	cin >> newdef;
	dict.editDef(word, newdef);
}

void add_word_menu(dictionary& dict) {
	string word, def;
	cout << "Enter the keyword: ";
	cin >> word;
	cout << "Enter the definition: ";
	cin >> def;
	dict.insert(word, def);
}

void remove_word_menu(dictionary& dict) {
	string word, temp;
	cout << "Enter the word you want to remove: ";
	cin >> word;
	dict.remove(word);
}