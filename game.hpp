#pragma once
#include "dictionary.hpp"
#define WIN32_LEAN_AND_MEAN
#include "graphic.hpp"

bool checkDuplicate(vector<entry*> vec);

void guess_keyword_meaning(dictionary dict);
void guess_definition_meaning(dictionary dict);