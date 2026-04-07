#include "Clue.h"
#include <cctype>
using namespace std;

// Fills in all the clue info called when we load from clues.txt
Clue::Clue(char sym, string q, string ans, int attempts, int pts) {
    symbol     = sym;
    question   = q;
    answer     = ans;
    maxAttempts = attempts;
    points     = pts;
    completed  = false;   // Nobody has answered it yet
}

// Converts every character in a string to lowercase to make answers case - insensitive
string Clue::toLower(const string& s) {
    string result = s;
    for (int i = 0; i < result.size(); i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

// Compares the player's guess to the stored answer
// Both sides get lowercased first so casing doesn't matter
bool Clue::checkAnswer(const string& guess) const {
    return toLower(guess) == toLower(answer);
}
