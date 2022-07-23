#pragma once
#include"dictionary.hpp"

struct dictionary_entry {
	string  name, filename;
};

void choose_dictionary();
void enter_dictionary_menu(dictionary<ASCII, ASCII>& dict, string dict_name);
void search_word(dictionary <ASCII, ASCII>& dict);
void search_definition(dictionary <ASCII, ASCII>& dict);
void add_word_menu(dictionary<ASCII, ASCII>& dict);
void remove_word_menu(dictionary<ASCII, ASCII>& dict);


