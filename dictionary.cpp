#include "dictionary.hpp"


void dictionary::write_text(tnode* root, std::ofstream& fout) {
	if (!root) return;
	if (!root->value.empty()) {
		auto ent = root->value.front().get();
		fout << ent->key << horizontal_tab << ent->value << "\n";
	}
	for (uint8_t i = 0; i < N_TYPE; ++i) {
		write_text(root->next[i], fout);
	}
}

void dictionary::read(std::ifstream& fin, tnode*& node, unsigned int& counter) {
	char ch = '\0';
	fin.read((char*)&(ch), sizeof(char));
	if (ch == horizontal_tab) node = nullptr;
	else {
		node = new tnode(N_TYPE, ch);
		size_t len = 0;
		fin.read((char*)&len, sizeof(size_t));
		if (len > 0) {
			char* buf_word = new char[len];
			fin.read(buf_word, len);
			std::string word(buf_word);
			delete[] buf_word;
			fin.read((char*)&len, sizeof(size_t));
			char* buf_def = new char[len];
			fin.read(buf_def, len);
			std::string def(buf_def);
			delete[] buf_def;
			shptr<entry> ent(new entry(word, def));
			node->value.push_back(ent);
			definition.insert(def, ent);
			++counter;
		}
		for (uint8_t i = 0; i < N_TYPE; ++i) {
			read(fin, node->next[i], counter);
		}
	}
}

void dictionary::write(std::ofstream& fout, tnode* node) {
	if (!node) fout.write((char*)&(horizontal_tab), sizeof(char));
	else {
		fout.write((char*)&(node->key), sizeof(char));
		size_t len = 0;
		if (node->value.empty()) fout.write((char*)&len, sizeof(size_t));
		else {
			//Write word
			len = node->value.front()->key.size() + 1;
			fout.write((char*)&len, sizeof(size_t));
			fout.write(node->value.front()->key.c_str(), len);
			//Write definition
			len = node->value.front()->value.size() + 1;
			fout.write((char*)&len, sizeof(size_t));
			fout.write(node->value.front()->value.c_str(), len);

		}
		for (uint8_t i = 0; i < N_TYPE; ++i) {
			write(fout, node->next[i]);
		}
	}
}
std::vector<std::string> dictionary::generate_words(const std::string& sentence) {
	std::stringstream ss(sentence);
	std::vector<std::string> vec;
	std::string word;
	while (getline(ss, word, ' ')) {
		for (char& ch : word) {
			ch = tolower(ch);
		}
		vec.push_back(word);
	}
	return vec;
}
dictionary::dictionary() {
	load = false;
	N_TYPE = 0;
}

dictionary::~dictionary() {
	load = false;
	N_TYPE = 0;
}

dictionary::dictionary(const std::string& path) {
	this->load = false;
	this->path = path;
	std::string filename = std::filesystem::path(path).filename().string();
	this->History = loadHistory(filename);
	this->Favourite = loadFavourite(filename);
	read(path);
	this->load = true;
}

dictionary::dictionary(const std::string& path, rmode mode) {
	this->load = false;
	this->path = path;
	std::string filename = std::filesystem::path(path).filename().string();
	this->History = loadHistory(filename);
	this->Favourite = loadFavourite(filename);
	if (mode == binary) {
		read(path);
	}
	else {
		read_text(path);
	}
	this->load = true;
}

dictionary::dictionary(const dictionary& _source) {
	load = _source.load;
	word = _source.word;
	N_TYPE = _source.N_TYPE;
	definition = _source.definition;
	path = _source.path;
	name = _source.name;
	History = _source.History;
	Favourite = _source.Favourite;
}

dictionary& dictionary::operator=(const dictionary& _source) {
	if (this != &_source) {
		load = _source.load;
		word = _source.word;
		N_TYPE = _source.N_TYPE;
		definition = _source.definition;
		path = _source.path;
		name = _source.name;
		History = _source.History;
		Favourite = _source.Favourite;
	}
	return *this;
}

void dictionary::read(const std::string& path) {
	if (load) clear();
	std::ifstream fin(path, std::ios::binary);
	if (fin) {
		//Read dictionary name
		size_t len = 0;
		fin.read((char*)&len, sizeof(size_t));
		char* buf = new char[len];
		fin.read(buf, len);
		name = std::string(buf);
		delete[] buf;
		//Read dictionary type
		uint32_t x = 0;
		fin.read((char*)&x, sizeof(uint32_t));
		N_TYPE = (uint8_t)x;
		this->word = trie(this->N_TYPE);
		unsigned int counter = 0;
		for (uint8_t i = 0; i < N_TYPE; ++i) {
			read(fin, word.top()->next[i], counter);
		}
		this->word.assign_count(counter);
	}
	else throw std::runtime_error("Error: ""BAD FILE AT " + path);
}

void dictionary::write() {
	std::ofstream fout(this->path, std::ios::binary);
	if (fout) {
		History.write();
		Favourite.write();
		//Write dictionary name
		size_t len = this->name.length() + 1;
		fout.write((char*)&len, sizeof(size_t));
		fout.write(this->name.c_str(), len);
		//Write dictionary type
		uint32_t x = 0;
		fout.write((char*)&N_TYPE, sizeof(uint32_t));

		for (uint8_t i = 0; i < N_TYPE; ++i) {
			write(fout, word.top()->next[i]);
		}
	}
	else throw std::runtime_error("Error: ""BAD FILE AT " + path);
}

void dictionary::read_text(const std::string& path) {
	if (load) clear();
	std::ifstream fin(path);
	if (fin) {
		std::string line, word, def;
		std::getline(fin, line); //get name
		this->name = line;
		std::getline(fin, line); //get dictionary type
		this->N_TYPE = (uint8_t)std::stoi(line);
		this->word = trie(this->N_TYPE); //initialize this->word
		unsigned int counter = 0;
		while (getline(fin, line)) {
			std::stringstream ss(line);
			std::getline(ss, word, '\t');
			std::getline(ss, def);
			insert(word, def);
			++counter;
		}
		this->word.assign_count(counter);
	}
}

void dictionary::write_text() {
	std::ofstream fout(path);
	fout.close();
	fout.open(path, std::ios::app);
	if (fout) {
		fout << name << "\n" << (uint32_t)N_TYPE << "\n";
		write_text(word.top(), fout);
	}
}
bool dictionary::insert(const std::string& word, const std::string& definition) {
	entry* temp = this->word.find(word);
	if (temp->value != definition) {
		shptr<entry> ent(new entry(word, definition));
		this->word.insert(ent);
		this->definition.insert(definition, ent);
		return true;
	}
	return false;
}

void dictionary::editDef(const std::string& keyword) {
	entry* temp = word.find(keyword);
	if (temp) {
		cout << "This word MEANS " << temp->value << endl;
		cout << "Enter the new definition: ";
		string newdef;
		getline(cin, newdef);
		if (temp->value != newdef) temp->value = newdef;
		cout << "\nEdit successfully";
	}
	else cout << "This word does not exist!";
}

void dictionary::remove(const std::string& word) {
	auto ent = this->word.find(word);
	if (!ent) cout << "This word doesn't exist!";
	else {
		this->word.remove(word);
		this->definition.remove(ent->value);
		cout << "\nRemove successfully";
	}
}
entry* dictionary::find_word(const std::string& word) {
	std::string time = currentDateTime();
	History.add_word_to_history(word, keyword,time);
	return this->word.find(word);
}
std::vector<entry*> dictionary::find_definition(const std::string& keyword) {
	std::string time = currentDateTime();
	History.add_word_to_history(keyword, def, time);
	auto vec = generate_words(keyword);
	if (vec.size() > 3) vec.resize(3);
	return definition.find(vec);
}


void dictionary::seeHistory() {
	History.printHistory();
}

std::string currentDateTime() {
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);
	char buffer[128];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %X", now);
	return buffer;
}

void dictionary::addWordToFavourtite(entry* temp) {
	if (!this->word.find(temp->key)) Favourite.mark(*temp);
}

bool dictionary::is_fav(string word) {
	return Favourite.isFavourite(word);
}

void dictionary::seeFavourite() {
	Favourite.display();
}

void dictionary::remove_fav(entry ent) {
	Favourite.remove(ent);
}

entry* dictionary::find_rand_word() {
	return word.random();
}

// check bug:
void dictionary::print_random_word() {
	entry* value = find_rand_word();
	std::cout << value->key << "  " << value->value << std::endl;

	return;
}
//Clear the entire dictionary
void dictionary::clear() {
	load = false;
	word.clear();
	definition.clear();
	N_TYPE = 0;
	path.clear();
	History.clear();
	Favourite.clear();
}

void dictionary::restore() {
	std::string t_path = path;
	clear();
	std::string temp = "data\\backup\\" + std::filesystem::path(t_path).filename().string();
	History.historyFilePath =  history_output + std::filesystem::path(t_path).filename().string() + ".txt";
	Favourite.favouriteFilepath = favourite_output + std::filesystem::path(t_path).filename().string() + ".txt";
	read(temp);
	load = true;
	path = t_path;
}

entry* dictionary::operator[](const std::string& _keyword) {
	return find_word(_keyword);
}


void dictionary::rename(const std::string& _source) {
	this->name = _source;
}

std::vector<std::string> get_list_of_files(const std::string& path) {
	std::vector<std::string> result;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		result.push_back(entry.path().string());
	}
	return result;
}

std::string get_dict_name(const std::string& path) {
	ifstream fin(path, std::ios::binary);
	//Read dictionary name
	size_t len = 0;
	fin.read((char*)&len, sizeof(size_t));
	char* buf = new char[len];
	fin.read(buf, len);
	std::string name = std::string(buf);
	delete[] buf;
	return name;
}