#include "menu.hpp"
#ifdef UNICODE
typedef LPWSTR LPTSTR;
#else
typedef LPSTR LPTSTR;
#endif




void choose_dictionary() {
	//Graphic:
	SetConsoleTitleA("DICTIONARY");
	srand((unsigned int)time(NULL));
	int opt = 1;
	int y = 7;
	char keyBoard = {};
	SetColor(15);
	string art = headline();

	system("cls");
	for (int i = 0; i < art.length(); i++) {
		cout << art[i];
		if (art[i] != ' ') {
			chrono::microseconds wait(10);
			this_thread::sleep_for(wait);
		}
	}

	vector<string> list_of_file = get_list_of_files(dictionary_path);
	vector<string> dict_name;
	for (auto i : list_of_file) dict_name.push_back(get_dict_name(i));

	//choose dictionary:
			system("cls");
			SetColor(rand() % 14 + 1);
			cout << art << endl;
			SetColor(15);
			menuDrawChooseDictionary(opt);
			do {
				ShowConsoleCursor(false);
				keyBoard = _getch();
				switch (keyBoard) {
				case KEY_DOWN:
					if (opt == 4) {
						opt = 1;
						menuDrawChooseDictionary(opt);
						y = 7;
					}
					else {
						opt++;
						y++;
						menuDrawChooseDictionary(opt);
					}
					break;

				case KEY_UP:
					if (opt == 1) {
						opt = 4;
						y = 11;
						menuDrawChooseDictionary(opt);
					}
					else {
						opt--;
						y--;
						menuDrawChooseDictionary(opt);
					}
					break;
				default:
					break;
				}
			} while (keyBoard != '\r');
			
			int choose;

			switch (opt) {
			case 1:
				choose = 1;
				break;
			case 2:
				choose = 2;
				break;
			case 3:
				choose = 3;
				break;
			case 4:
				choose = 4;
				break;
			}



/*
* 		cout << "Welcome to our dictionary!\n";
		cout << "Here is the list of dictionary:\n";
		for (int i = 0; i < dict_name.size(); ++i) cout <<
			i + 1 << ". " << dict_name[i] << ".\n";
		cout << "Please choose the dictionary: ";
		int choose;
		cin >> choose;
*/

		gotoxy(31, 14);
		std::cout << "Please wait for a minute\n";
		enter_dictionary_menu(dict_name[choose -  1],list_of_file[choose - 1]);

	
}

void enter_dictionary_menu(string& name,string& path) {
	dictionary dict(path, binary);

RETURN_MENU:
	// graphic:
	int opt = 1;
	int y = 7;
	int row = 0;
	char keyBoard = {};
	string art = headline();
	system("cls");
	SetColor(rand() % 14 + 1);
	cout << art << endl;

	SetColor(15);


	menuDrawEnterDictionary(opt);
	do {
		ShowConsoleCursor(false);
		keyBoard = _getch();
		switch (keyBoard) {
		case KEY_DOWN:
			if (opt == 13) {
				opt = 1;
				menuDrawEnterDictionary(opt);
				y = 7;
			}
			else {
				opt++;
				y++;
				menuDrawEnterDictionary(opt);
			}
			break;

		case KEY_UP:
			if (opt == 1) {
				opt = 13;
				y = 20;
				menuDrawEnterDictionary(opt);
			}
			else {
				opt--;
				y--;
				menuDrawEnterDictionary(opt);
			}
			break;
		default:
			break;
		}
	} while (keyBoard != '\r');

	/*
	//choose function: 
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
	cout << "12. Choose another dictionary.\n";
	cout << "0. EXIT";
	cout << "Your choice: ";
	int choose;
	cin >> choose;
	cout << endl;	
	*/


	system("cls");

	ShowConsoleCursor(true);

	switch (opt) {
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
	case 7: 
		dict.restore();
		system("cls");
		cout << "Restore successfully!";
		chrono::seconds duration(1);
		this_thread::sleep_for(duration);
		break;
	case 8: 
		dict.print_random_word();
		_getch();
		this_thread::sleep_for(duration);
		break;
	case 9:Fav_menu(dict);
		this_thread::sleep_for(duration);
		break;
	case 10:guess_definition_meaning(dict);
		break;
	case 11:	guess_keyword_meaning(dict);
		this_thread::sleep_for(duration);
		break;
	case 12:
		dict.write();
		choose_dictionary();
		break;
	default:
		dict.write();
		for (int i = 3; i > 0; i--) {
			ShowConsoleCursor(false);
			system("cls");
			gotoxy(31, 14);
			cout << "Good bye! The program will exit in " << i << " seconds.\r";
			chrono::seconds duration(1);
			this_thread::sleep_for(duration);
		}
		gotoxy(31, 14);
		std::cout << "Good bye! The program will exit in 0 seconds.\n";
		ShowConsoleCursor(true);

		dict.write();
		exit(0);
		return;
		
	}

	goto RETURN_MENU;




	//enter_dictionary_menu(name, path);
}

void search_word(dictionary& dict) {
	cout << "Enter the word you want to find: ";
	string s;
	getline(cin,s);
	entry* temp = dict.find_word(s);
	if (!temp) cout << "This word doesn't exist!";
	else {
		cout << "The word you want to find is: " << temp->key << " MEANS " << temp->value << endl;
		char t = '\0';
		if (dict.is_fav(s)) {
			cout << "Press F to remove this word from the favourite list, "
				<< "ENTER to continue/return.";
			do {
				t = tolower(_getch());
			} while ((t != '\r') && (t != 'f'));
			if (t == 'f') {
				dict.remove_fav(*temp);
				cout << "Removed successfully!";
				
			}
		}
		else {
			cout << "Press F to add this word to the favourite list, "
				<< "ENTER to continue/return.";
			do {
				t = tolower(_getch());
			} while ((t != '\r') && (t != 'f'));
			if (t == 'f') {
				dict.addWordToFavourtite(temp);
				cout << "Added successfully.";
			}
		}
	}
	this_thread::sleep_for(chrono::seconds(1));
}

void search_definition(dictionary& dict) {
	cout << "Enter the definition you want to find: ";
	string s;
	getline(cin, s);
	vector<entry*> temp = dict.find_definition(s);
	if (temp.empty()) cout << "No such definition";
	else {
		cout << "Here is the list of word that matches your definition:\n";
		int limit = std::min((int)(temp.size()), 10);
		for (int i = 0; i < limit; ++i) {
			cout << i + 1 << ". " << temp[i]->key << " " << temp[i]->value << endl;
		}
	}
	cout << "\nPress any key to continue..." << endl;
	_getch();
}

void edit_def_menu(dictionary& dict) {
	cout << "Enter the word you want to change definition: ";
	string word;
	getline(cin, word);
	dict.editDef(word);
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
}

void add_word_menu(dictionary& dict) {
	string word, def;
	cout << "Enter the keyword: ";
	getline(cin,word);
	cout << "Enter the definition: ";
	getline(cin, def);
	if (dict.insert(word, def)) {
		cout << "\nAdd successfully";
	}
	else {
		cout << "\nWord \"" << word << "\" already exists";
	}
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
}

void remove_word_menu(dictionary& dict) {
	string word, temp;
	cout << "Enter the word you want to remove: ";
	getline(cin, word);
	dict.remove(word);
	chrono::seconds duration(1);
	this_thread::sleep_for(duration);
}

void Fav_menu(dictionary& dict) {
	system("cls");
	dict.seeFavourite();
	cout << "\nAvailable options: ";
	cout << "\n(A)     Add new word.";
	cout << "\n(R)     Remove word.";
	cout << "\n(ENTER) Return to main menu\n";
	char choose = '\0';
	do {
		choose = tolower(_getch());
	} while ((choose != 'a') && (choose != 'r') && (choose != '\r'));
	switch (choose) {
	case 'a': {
		string s;
		cout << "Enter key word: ";
		getline(cin, s);
		entry* ent = dict.find_word1(s);
		if (!ent) {
			cout << "This word doesn't exist!";
			this_thread::sleep_for(chrono::seconds(1));
		}
		else {
			dict.addWordToFavourtite(ent);
			cout << "Added successfully!";
			this_thread::sleep_for(chrono::seconds(1));
		}
		break;
	}
	case 'r': {
		string s;
		cout << "Enter key word: ";
		getline(cin,s);
		entry* ent = dict.find_word(s);
		if (!ent) {
			cout << "This word doesn't exist!";
			this_thread::sleep_for(chrono::seconds(1));
		}
		else {
			dict.remove_fav(*ent);
			cout << "Removed successfully!";
			this_thread::sleep_for(chrono::seconds(1));
		}
		break;
	}
	case '\r':
		break;
	default: 
		break;
	}	
	
}