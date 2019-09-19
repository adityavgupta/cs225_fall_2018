/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	ifstream wordsFile(filename);
	string word;
	if(wordsFile.is_open()) {
		while(getline(wordsFile, word)) {
			std::string w1(word);
			std::sort(w1.begin(), w1.end());
			dict[w1].push_back(word);
		}
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
	for(std::string w : words) {
		std::string w1(w);
		std::sort(w1.begin(), w1.end());
		dict[w1].push_back(w);
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	std::string w(word);
	std::sort(w.begin(), w.end());
	if(dict.count(w) == 0)
		return vector<string>();
	return dict.at(w); 
    //return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	std::vector<std::vector<std::string>> all_anagrams;
	for(std::pair<std::string, std::vector<std::string>> key_val : dict) {
		std::vector<string> anag = key_val.second;
		if(anag.size() < 2) continue;
		all_anagrams.push_back(anag);
	}
    return all_anagrams;
}
