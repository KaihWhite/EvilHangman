/*
    hangman.cpp

    author: Kaih White
*/

#include "hangman.h"
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <map>

#define print(x) cout << x << endl

using namespace std;

string occ(string s, char c){
    string spots(s.size(), '-');
    for(int i = 0; i < s.size(); i++){
        if(s[i] == c){
            spots[i] = c;
        }
    }
    return spots;
}

// constructor
hangman::hangman() { 
    ifstream di("dictionary.txt");

    string placeholder;
    while (! di.eof()){
        di >> placeholder;
        dict.insert(placeholder);
    }
    di.close();
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int word_length) {

    possiblewords.clear();
    for (const auto & iter : dict){
        if(iter.size() == word_length){
            possiblewords.insert(iter);
        }
    }

    word.clear();
    word.resize(word_length, '-');
    guessed.clear();
    lettersinfinal.clear();
    guessesleft = num_guesses;
    win = 0;
    finword.clear();
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {

    set<string> pset = possiblewords, lol;
    map<string, int> check;

    for (auto iter = possiblewords.begin();iter != possiblewords.end(); iter++){
        if(iter -> find(c) != string::npos){
            lol.insert(*iter);
            pset.erase(*iter);
        }
    }

    for (const auto & iter : lol) {
        if(check.count(occ(iter, c))){
            check[occ(iter, c)]++;
        }
        else{
            check.insert(pair<string, int>(occ(iter, c), 1));
        }
    }

    int max = 0;
    string wordp;
    for (auto iter = check.begin(); iter != check.end(); iter++) {
        if(iter -> second > max){
            max = iter -> second;
            auto itermax = iter;
            wordp = iter -> first;
        }
    }

    if(max > pset.size()){

        vector<int> spaces{};
        set<string> fin{};
        lettersinfinal.insert(c);

        for(int i = 0; i < wordp.size();i++){
            if(wordp[i] == c){
                word[i] = c;
                spaces.push_back(i);
            }
        }

        int correct = spaces.size();
        for (const auto & iter : lol) {
            int count = 0;
            for(int j = 0; j < iter.size(); j++){
                if(iter[j] == c) {
                    for (int l : spaces) {
                        if (l == j) {
                            count++;
                        }
                        else{
                            count--;
                        }
                    }
                }
            }
            if(count == correct){
                fin.insert(iter);
            }
        }
        possiblewords = fin;

        return true;
    }
    else{
        guessesleft--;
        possiblewords = pset;
        return false;
    }
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return word;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return guessesleft;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    string g;
    for (const auto & iter : guessed) {
        g.push_back(iter);
    }
    return g;
}



// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    if (guessed.count(c)){
        return true;
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    for(char o : word){
        if(o == '-'){
            return false;
        }
    }
    return true;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if(guessesleft < 1){
        return true;
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    string wordf;
    for(const auto & iter : possiblewords){
        wordf = iter;
        break;
    }
    return wordf;
}


