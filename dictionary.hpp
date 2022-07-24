#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include "history.hpp"
#include "ds\linear_finder.hpp"
#include "ds\trie.hpp"
#include "favourites.hpp"

static constexpr char horizontal_tab = '\t';
static constexpr char dictionary_path[] = "data\\dictionaries\\";

enum rmode {
	text = 0, binary = 1
};

class dictionary {
private:
	bool load; // variable for checking whether the dictionary is loaded
	trie word; // word trie
	uint8_t N_TYPE;// trie type
	linear_finder definition; // definition string for searching
	std::string path; // path to file
	std::string name; // display name of the dictionary
	history History;
	fav_word Favourite;
	//Write to binary file (recursive function)
	void write_text(tnode* root, std::ofstream& fout);
	//Read from binary file (recursive function)
	void read(std::ifstream& fin, tnode*& node, unsigned int& counter);
	//Write to binary file (recursive function)
	void write(std::ofstream& fout, tnode* node);
public:
	dictionary();
	~dictionary();
	//Default constructor, binary file mode
	dictionary(const std::string& path);
	//Default constructor, optional file mode
	dictionary(const std::string& path, rmode mode);
	//Copy constructor
	dictionary(const dictionary& _source);
	//Copy assignment
	dictionary& operator=(const dictionary& _source);
	//Read from binary file
	void read(const std::string& path);
	//Write to binary file
	void write();
	//Read from text file
	void read_text(const std::string& path);
	//Write to text file
	void write_text();
	void insert(const std::string& word, const std::string& definition);
	void remove(const std::string& word);
	entry* find_word(const std::string& word);
	std::vector<entry*> find_definition(const std::string& keyword);

	void seeHistory();

	void addWordToFavourtite(entry* temp);

	void seeFavourite();

	entry* find_rand_word();

	// check bug:
	void print_random_word();
	//Clear the entire dictionary
	void clear();

	void restore();
	//Act like find_word
	entry* operator[](const std::string& _keyword);
	//Rename the dictionary
	void rename(const std::string& _source);
};

//How to get a list of file in a folder
std::vector<std::string> get_list_of_files(const std::string& path);
std::string get_dict_name(const std::string& path);