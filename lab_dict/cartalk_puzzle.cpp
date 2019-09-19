/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
	std::tuple<std::string, std::string, std::string> t;
	ifstream wordsFile(word_list_fname);
	string word;
	if(wordsFile.is_open()) {
		while(getline(wordsFile, word)) {
			string w1 = word.substr(1);
			string w2 = word[0] + word.substr(2);

			//std::cout<< w1 << std::endl;
			//std::cout<< w2 << std::endl;
			if(d.homophones(word, w1) && d.homophones(word, w2) && d.homophones(w1, w2)) {
				t = make_tuple(word, w1, w2);
				ret.push_back(t);
			}
		}
	}
    return ret;
}
