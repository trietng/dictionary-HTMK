#pragma once
#include"dictionary.hpp"

struct dictionary_entry {
	string  name, filename;
};

void choose_dictionary();
void enter_dictionary_menu(dictionary& dict, string dict_name);
void search_word(dictionary& dict);
void search_definition(dictionary& dict);
void add_word_menu(dictionary& dict);
void remove_word_menu(dictionary& dict);


