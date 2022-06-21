#include"editWords.hpp"

void add_word_menu(dictionary& dict){
    string word, def, temp;
    bool check = false;
    do {
        cout << "Enter the keyword: ";
        cin >> word;
        cout << "Enter the definition: ";
        cin >> def;
        if (dict.find_word(word)) dict.insert(word,def);
        else cout << "Your word already exists.\n";
        cout << "You want to insert another word? (y/n): ";
        cin >> temp;
        check = (temp == "y");
    }while (check);
}

void remove_word_menu(dictionary& dict){
    string word, temp;
    bool check = false;
    do {
        cout << "Enter the word you want to remove: ";
        cin >> word;
        if (dict.find_word(word)) dict.remove(word);
        else cout << "Your word is not in our data: \n";
        cout << "You want to remove another word? (y/n): ";
        cin >> temp;
        check = (temp == "y");
    }while (check);
}

void edit_word_menu(dictionary& dict){
    string word, def, temp;
    bool check = false;
    do {
        cout << "Enter the keyword: ";
        cin >> word;
        if (dict.find_word(word)) {
            cout << "Enter the definition you want to change: ";
            cin >> def;
            dict.remove(word);
            dict.insert(word,def);
        }
        else cout << "Your word doesn't exist.\n";
        cout << "You want to insert another word? (y/n): ";
        cin >> temp;
        check = (temp == "y");
    }while (check);
}

