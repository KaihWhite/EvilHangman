#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h

    author: Kaih White
*/

#include <string>
#include <set>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses, int word_length);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

    set<string> dict;
    set<char> guessed;
    set<char> lettersinfinal;
    set<string> possiblewords;
    string word;
    int guessesleft;
    bool win;
    string finword;

private:
    
};

#endif
