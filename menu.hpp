#pragma once
#include"dictionary.hpp"
#include"game.hpp"

struct dictionary_entry {
	string  name, filename;
};

void choose_dictionary();
void enter_dictionary_menu(string& name, string& path);
void search_word(dictionary& dict);
void search_definition(dictionary& dict);
void edit_def_menu(dictionary& dict);
void add_word_menu(dictionary& dict);
void remove_word_menu(dictionary& dict);


