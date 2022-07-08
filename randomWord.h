/*#pragma once
#include <random>
#include <iostream>
using namespace std;
class TrieNode {
public:
    TrieNode() : rng(dev()), nodes{ 0 }, word_count{ 0 } {}

    ~TrieNode() {
        for (TrieNode* node : nodes) {
            if (node) delete node;
        }
    }

    // return a random string
    string random() {
        uniform_int_distribution<mt19937::result_type> dist(0, word_count - 1);
        return at(dist(rng));
    }

    // return the string at a given index
    string at(int index) {
        string word = "";
        at(index, word, 0);
        return word;
    }

    void add(const string word) {
        add(word, 0);
    }

protected:
    void at(int index, string& word, int depth) {
        int sum = 0;
        for (int i = 0; i < 27; i++) {
            TrieNode* node = nodes[i];
            if (!node || node->word_count == 0) continue;

            int size = node->word_count;
            if (index < sum + size) {
                if (i == 26) {
                    word = string(depth, ' ');
                }
                else {
                    node->at(index - sum, word, depth + 1);
                    word[depth] = 'a' + i;
                }
                return;
            }
            sum += size;
        }
    }

    void add(const string& word, int index) {
        word_count++;
        if (index == word.length()) {
            if (!nodes[26]) nodes[26] = new TrieNode();
            nodes[26]->word_count++;
        }
        else {
            int c = word[index] - 'a';
            if (!nodes[c]) nodes[c] = new TrieNode();
            nodes[c]->add(word, index + 1);
        }
    }

    int word_count;
    TrieNode* nodes[27]; // a-z and a terminator only
    random_device dev;
    mt19937 rng;
};

*/