#pragma once
#include "dictionary.hpp"
#include<iostream>
#include<fstream>
#include <string>

using namespace std;

void add_word_menu(dictionary<ASCII,ASCII>& dict);
void remove_word_menu(dictionary<ASCII,ASCII>& dict);
void edit_word_menu(dictionary<ASCII,ASCII>& dict);